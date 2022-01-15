# FINANCE

es un código sobre una página completa y de bolsa de valores

1) primero tenemos que crear una tabla en la base de datos  de donde se guarde todas las transacciones y agregar variables para las queras

2) comenzaremos por orden `register` `quote` `index` `buy` `sell` y `history`

3) en `register` colocaremos validaciones sobre el registro de usuario y confirmación de contraseña, luego de ello ingresaremos al usuario de la base de datos, creamos template de `registro.html` de manera de formulario

4) `quote` quote es una vista al precio de las acciones que el usuario quisiera comprar, creamos `quote.html`con formato formulario 

5) `index` se ingresará  como página principal estará guardado los datos del usuario desde su dinero hasta sus acciones compradas, en su `index.html` tendrá un formato de tablas que se reúne toda la información del usuario 

6) `buy` en el se comprara las acciones que el usuario solicite y cada acción comprada se registrará en la base de datos y eliminara el dinero gastado al usuario todo esto irá reflejado en `index.html`, su página `buy.html` será un formato formulario

7) `sell` tendría como tal tener acciones compradas para luego venderla tendría que ser una acción positiva para luego eliminar en la base de datos la acción vendida y en su dinero tener el usuario la inversión al vender la acción, su `sell.html` es un formulario con donde tiene guardado los símbolos de las acciones al poder del usuario 

8)  `history` como tal da toda la actividad de compras y ventas de acciones del usuario 

