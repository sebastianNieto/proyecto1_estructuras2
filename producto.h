struct Producto
{
	int id;
	char nombre[30];
	float valor;
	int cantidad;
} productos, *pproductos = &productos;

int subOpcion, i =0;

void encabezado_producto(int y)
{
	color(amarillo);
	dibujaRectangulo(12,y-1,68,y+1,'\372');
	color(grisclaro);
	gotoxy(13, y);printf("Id");
	color(amarillo);
	gotoxy(16, y);printf("\263");
	color(grisclaro);
	gotoxy(17, y);printf("Nombre");
	color(amarillo);
	gotoxy(48, y);printf("\263");
	color(grisclaro);
	gotoxy(49, y);printf("Valor");
	color(amarillo);
	gotoxy(59, y);printf("\263");
	color(grisclaro);
	gotoxy(60, y);printf("Cantidad");
}

void cuerpo_producto(Producto *pproductos, int y)
{
	color(amarillo);
	dibujaRectangulo(12,y-1,68,y+1,'\372');
	color(grisclaro);
	gotoxy(13, y);printf("%d", pproductos->id);
	color(amarillo);
	gotoxy(16, y);printf("\263");
	color(grisclaro);
	gotoxy(17, y);printf("%s", pproductos->nombre);
	color(amarillo);
	gotoxy(48, y);printf("\263");
	color(grisclaro);
	gotoxy(49, y);printf("%.2f", pproductos->valor);
	color(amarillo);
	gotoxy(59, y);printf("\263");
	color(grisclaro);
	gotoxy(60, y);printf("%d", pproductos->cantidad);
};

bool crear_productos()
{
	FILE *archivo;
	
	archivo = fopen("datos/productos.txt", "rb");
	
	if(archivo == NULL)
	{
		return false;
	}
	rewind(archivo);
	fseek(archivo,ftell(archivo)-sizeof(*pproductos),SEEK_END);
	fread(pproductos, sizeof(*pproductos), 1, archivo);
	pproductos->id = pproductos->id+1;
	fclose(archivo);
	color(azulclaro);
	fflush(stdin);
	gotoxy(24,7);printf("Nombre del producto");
	color(azulclaro);
	gotoxy(24,8);fgets(pproductos->nombre, 30, stdin);
	fflush(stdin);
	color(azulclaro);
	gotoxy(24,10);printf("Valor del Producto");
	color(azulclaro);
	gotoxy(24,11);scanf("%f", &pproductos->valor);
	gotoxy(24,13);printf("Cantidad del Producto");
	color(azulclaro);
	gotoxy(24,14);scanf("%d", &pproductos->cantidad);
	
	archivo = fopen("datos/productos.txt", "ab");
	
	if(archivo == NULL)
	{
		color(rojoclaro);
		gotoxy(24, 16);printf("No se pudo guardar el registro");
	}
	else
	{
		fwrite(pproductos,sizeof(*pproductos),1,archivo);
		rewind(archivo);
		fclose(archivo);
		color(verdeclaro);
		gotoxy(32, 16);printf("Registro Exito");
	}
}

bool mostrar_productos()
{
	FILE *archivo;
	int y = 7;
	
	archivo = fopen("datos/productos.txt", "rb");
	
	if(archivo == NULL)
	{
		return false;
	}
	else
	{
		gotoxy(29, 3);printf("Listado de productos");
		encabezado_producto(5);
		while(fread(pproductos, sizeof(*pproductos), 1, archivo))
		{
			cuerpo_producto(pproductos, y);
			y+=2;
		}
	}
	fclose(archivo);
}

void producto_encontrado(int *pIndice)
{
	FILE *archivo;
	
	color(verdeclaro);
	gotoxy(29, 3);printf("Registro Encontrado");
	archivo = fopen("datos/productos.txt", "rb");
	fseek(archivo,sizeof(*pproductos)* *pIndice,SEEK_SET);
	encabezado_producto(5);
	cuerpo_producto(pproductos, 7);
	fclose(archivo);
}

int buscar_producto(int *pBuscar)
{
	FILE *archivo;
	int indice = 0, *pIndice = &indice;
	bool bandera = false, *pBandera = &bandera;
	archivo = fopen("datos/productos.txt", "rb");
	
	if(archivo == NULL)
	{
		return false;
	}
	else
	{
		while(fread(pproductos, sizeof(*pproductos), 1, archivo))
		{
			(*pIndice)++;
			if(*pBuscar == pproductos->id)
			{
				*pBandera = true;
				break;
			}
		}
		fclose(archivo);
		if(!*pBandera)
		{
			return 0;
		}
		else
		{
			return *pIndice;
		}
	}
}

void editar_producto(int *pUbicacion){
	
	int opcion = 0, *pOpcion = &opcion;
	
	FILE *archivo;
	archivo = fopen("datos/productos.txt", "rb+");
	fseek(archivo,sizeof(*pproductos)* ((*pUbicacion) - 1),SEEK_SET);
	
	do{
		color(amarillo);
		gotoxy(30,10);printf(" EDITAR PRODUCTO ");
		gotoxy(17,12);printf("1. Nombre ");
		gotoxy(17,13);printf("2. Valor ");
		gotoxy(17,14);printf("3. Cantidad ");
		gotoxy(17,14);printf("0. Salir");
		color(verde);
		gotoxy(17,16);printf(" Seleccione la opcion que desea Modificar: ");
		scanf("%d", &opcion);
		switch (*pOpcion)
		{
			case 1:
			{
				color(verde);
				gotoxy(28,21);printf("Ingrese el nuevo nombre: ");
				fflush(stdin);
				color(grisclaro);
				gotoxy(28,22);fgets(pproductos->nombre, 30, stdin);
				fwrite(pproductos,sizeof(*pproductos),1,archivo);
				break;
			}
			case 2:
			{
				color(verde);
				gotoxy(28,21);printf("Ingrese el nuevo valor: ");
				fflush(stdin);
				color(grisclaro);
				gotoxy(28,22);fgets(pUsuario->cedula, 10, stdin);
				fwrite(pproductos,sizeof(*pproductos),1,archivo);
				break;
			}
			case 3:
			{
				color(verde);
				gotoxy(28,21);printf("Ingrese la nueva cantidad: ");
				fflush(stdin);
				color(grisclaro);
				gotoxy(28,22);fgets(pUsuario->cedula, 10, stdin);
				fwrite(pproductos,sizeof(*pproductos),1,archivo);
				break;
			}
		}
		if(*pOpcion != 0)
		{
			system("cls");
			producto_encontrado(pUbicacion);
		}
	}while(*pOpcion!=0);
	fclose(archivo);
}

