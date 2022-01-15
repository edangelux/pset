from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure responses aren't


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    total = 0
    usuario_actual = session["user_id"]
    accion = db.execute("SELECT * FROM portafolio WHERE id = :id_", id_=usuario_actual)
    lista_precios = []

    # VALIDAR NO MUESTRE ACCIONES EN 0
    mostrar = []
    for i in accion:
        if i["shares"] != 0:
            mostrar.append(i)

    # creando lista de portafolio para que se muestre
    for i in mostrar:
        info = lookup(i["symbol"])
        i["price"] = info["price"]
        i["total"] = i["shares"] * i["price"]
        total += i["total"]

    # consiguiendo dinero usuario
    rows = db.execute("SELECT cash FROM users WHERE id = :id_", id_=usuario_actual)
    dinero_actual = rows[0]["cash"]
    total += dinero_actual
    return render_template("index.html", mostrar=mostrar, cash=dinero_actual, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":

        # VALIDACIONES SI NO SE INGRESAN COSAS
        if not request.form.get("symbol"):
            return apology("ENTER A SYMBOL")

        elif not request.form.get("shares"):
            return apology("ENTER THE SHARES")

        info = lookup(request.form.get("symbol"))

        if info == None:
            return apology("ENTER A VALID SYMBOL")

        # VALIDACION NUMERO
        try:
            shares = int(request.form.get("shares"))
        except ValueError:
            return apology("ENTER A VALID SHARE NUMBER")

        # SI EL NUMERO ES 0

        if shares <= 0:
            return apology("ENTER A VALID SHARE NUMBER")

        # consiguiendo precio actual accion
        current_price = info["price"]

        # consiguiendo simbolo
        simbolo = info["symbol"]

        # consiguiendo el id del usuario para buscarlo en la db
        usuario_actual = session["user_id"]

        # consiguiendo nombre accion
        nombre_accion = info["name"]

        # consiguiendo el dinero actual restante del usuario
        rows = db.execute("SELECT cash FROM users WHERE id = :id_",
                          id_=usuario_actual)

        dinero_actual = rows[0]["cash"]

        # VALIDACION SI EL USUARIO PUEDE HACER LA COMPRA
        if(dinero_actual > shares * current_price):
            # agregando a historial
            shares_str = f"+{shares}"
            db.execute("INSERT INTO historial (id,symbol,shares,price,name) VALUES (?,?,?,?,?)",
                       usuario_actual, simbolo, shares_str, current_price, nombre_accion)

            # restando dinero de la cuenta
            db.execute("UPDATE users SET cash = :cash_cambiado WHERE id = :id_",
                       cash_cambiado=dinero_actual - (shares * current_price), id_=usuario_actual)

            # agregando a portafolio

            # checkeando si ya tenia una accion previamente
            accion = db.execute("SELECT * FROM portafolio WHERE symbol = :symbol AND id = :id_", symbol=simbolo, id_=usuario_actual)
            # no existia
            if len(accion) == 0:
                db.execute("INSERT INTO portafolio (id,symbol,name,shares) VALUES (?,?,?,?)",
                           usuario_actual, simbolo, nombre_accion, shares)
                return redirect("/")
                # existia
            else:
                actualizar = db.execute("SELECT * from portafolio WHERE symbol = :symbol AND id = :id_",
                                        symbol=simbolo, id_=usuario_actual)
                shares_actuales = actualizar[0]["shares"]
                shares_actuales += shares

                db.execute("UPDATE portafolio SET shares = :shares_ WHERE symbol = :symbol AND id = :id_",
                           shares_=shares_actuales, symbol=simbolo, id_=usuario_actual)

            return redirect("/")
        else:
            return apology("NOT ENOUGH MONEY")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # SE CONSIGUE TODAS LAS ACCIONES DEL USUARIO DE LA DB BASANDOSE EN SU ID
    usuario_actual = session["user_id"]
    historial = db.execute("SELECT * FROM historial WHERE id = :id_", id_=usuario_actual)
    return render_template("history.html", historial=historial)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password")

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # VALIDACION SI NO SE METIO ALGO
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("Symbol required")

        info = lookup(request.form.get("symbol"))

        # VALIDACION SI LA ACCION NO EXISTE
        if info == None:
            return apology("Symbol not found")
        return render_template("quoted.html", info=info)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        # VALIDACIONES SI NO SE INTRODUJO ALGO
        if not request.form.get("username"):
            return apology("must provide username")

        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # VALIDACION NO PODER CREAR DOS USUARIOS CON EL MISMO NOMBRE
        for i in rows:
            if(i["username"] == request.form.get("username")):
                return apology("user already taken")

        # VALIDACION USUARIO DE ESPACIO VACIO
        if request.form.get("username") == " ":
            return apology("enter a valid username")

        if not request.form.get("password"):
            return apology("must provide password")

        # VALIDACION QUE AMBAS CONTRASEÑAS SEAN IGUALES
        elif not request.form.get("confirmation"):
            return apology("must repeat the password")

        if(request.form.get("confirmation") != request.form.get("password")):
            return apology("passwords must be equal")

        # SE INTRODUCE EL USUARIO A LA BD
        db.execute("INSERT INTO users (username,hash) VALUES (?,?)", request.form.get(
            "username"), generate_password_hash(request.form.get("password")))

        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    else:
        return render_template("register.html")

# TOQUE PERSONAL AGREGAR DINERO A LA CUENTA


@app.route("/addmoney", methods=["GET", "POST"])
@login_required
def addmoney():
    if request.method == "POST":

        # VALIDACION NO SE INTRODUCEN COSAS
        if not request.form.get("money"):
            return apology("ENTER THE MONEY")

        # VALIDACION DINERO NUMERO
        try:
            dinero = int(request.form.get("money"))
        except ValueError:
            return apology("ENTER A VALID NUMBER")

        # VALIDACION DINERO POSITIVO
        if dinero <= 0:
            return apology("ENTER A VALID NUMBER")

        # consiguiendo el id del usuario para buscarlo en la db
        usuario_actual = session["user_id"]

        # consiguiendo el dinero actual restante del usuario
        rows = db.execute("SELECT cash FROM users WHERE id = :id_",
                          id_=usuario_actual)

        dinero_actual = rows[0]["cash"]

        # sumando dinero de la cuenta
        db.execute("UPDATE users SET cash = :cash_cambiado WHERE id = :id_",
                   cash_cambiado=dinero_actual + dinero, id_=usuario_actual)

        return redirect("/")

    else:
        return render_template("addmoney.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":

        # VALIDACION NO SE INTRODUCEN COSAS
        if not request.form.get("symbol"):
            return apology("ENTER A SYMBOL")

        if not request.form.get("shares"):
            return apology("ENTER HOW MANY SHARES")

        # VALIDACION ACCIONES NUMERO
        try:
            acciones_seleccionadas = int(request.form.get("shares"))

        except ValueError:
            return apology("ENTER A VALID NUMBER")

        # VALIDACION ACCIONES POSITIVAS
        if acciones_seleccionadas <= 0:
            return apology("ENTER A VALID NUMBER")

        opcion = request.form.get("symbol")

        info = lookup(opcion)

        usuario_actual = session["user_id"]

        # CONSIGUIENDO PORTAFOLIO PARA ACTUALIZARLO
        accion = db.execute("SELECT * FROM portafolio WHERE id = :id_ AND symbol = :symbol_", id_=usuario_actual, symbol_=opcion)

        acciones_usuario = accion[0]["shares"]

        # validando que el usuario tengo las acciones que desea vender

        if acciones_usuario < acciones_seleccionadas:
            return apology("NOT ENOUGH SHARES")

        else:
            # consiguiendo el dinero actual restante del usuario
            rows = db.execute("SELECT cash FROM users WHERE id = :id_",
                              id_=usuario_actual)

            dinero_actual = rows[0]["cash"]

            # actualizando dinero del usuario

            current_price = info["price"]

            db.execute("UPDATE users SET cash = :cash_cambiado WHERE id = :id_", cash_cambiado=dinero_actual +
                       (acciones_seleccionadas * current_price), id_=usuario_actual)

            # actualizando numero de acciones

            shares_actuales = acciones_usuario - acciones_seleccionadas
            db.execute("UPDATE portafolio SET shares = :shares_ WHERE symbol = :symbol AND id = :id_",
                       shares_=shares_actuales, symbol=opcion, id_=usuario_actual)

            # actualizando historial
            nombre_accion = info["name"]
            shares_str = f"-{acciones_seleccionadas}"
            db.execute("INSERT INTO historial (id,symbol,shares,price,name) VALUES (?,?,?,?,?)",
                       usuario_actual, opcion, shares_str, current_price, nombre_accion)
            return redirect("/")
    else:
        # SE CREA UNA LISTA QUE SERA EL PORTAFOLIO, SOLO MOSTRARA LAS ACCIONES MAYORES A 0
        opciones = []
        usuario_actual = session["user_id"]
        accion = db.execute("SELECT * FROM portafolio WHERE id = :id_", id_=usuario_actual)
        for i in accion:
            if i["shares"] > 0:
                opciones.append(i["symbol"])
        return render_template("sell.html", opciones=opciones)


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
