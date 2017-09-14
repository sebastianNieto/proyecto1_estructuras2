struct Producto
{
	int id;
	char nombre[30];
	float valor;
	int cantidad;
	int vendida;
} productos, *pproductos = &productos;

int subOpcion, i =0;

void encabezado_producto(int y)
{
	color(amarillo);
	dibujaRectangulo(8,y-1,73,y+1,'\372');
	color(grisclaro);
	gotoxy(9, y);printf("Id");
	color(amarillo);
	gotoxy(12, y);printf("\263");
	color(grisclaro);
	gotoxy(13, y);printf("Nombre");
	color(amarillo);
	gotoxy(44, y);printf("\263");
	color(grisclaro);
	gotoxy(45, y);printf("Valor");
	color(amarillo);
	gotoxy(55, y);printf("\263");
	color(grisclaro);
	gotoxy(56, y);printf("Cantidad");
	color(amarillo);
	gotoxy(64, y);printf("\263");
	color(grisclaro);
	gotoxy(65, y);printf("Vendidos");
}

void cuerpo_producto(Producto *pproductos, int y)
{
	color(amarillo);
	dibujaRectangulo(8,y-1,73,y+1,'\372');
	color(grisclaro);
	gotoxy(9, y);printf("%d", pproductos->id);
	color(amarillo);
	gotoxy(12, y);printf("\263");
	color(grisclaro);
	gotoxy(13, y);printf("%s", pproductos->nombre);
	color(amarillo);
	gotoxy(44, y);printf("\263");
	color(grisclaro);
	gotoxy(45, y);printf("%.2f", pproductos->valor);
	color(amarillo);
	gotoxy(55, y);printf("\263");
	color(grisclaro);
	gotoxy(56, y);printf("%d", pproductos->cantidad);
	color(amarillo);
	gotoxy(64, y);printf("\263");
	color(grisclaro);
	gotoxy(65, y);printf("%d", pproductos->vendida);
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
	fflush(stdin);
	color(amarillo);
	gotoxy(24,7);printf("Nombre del producto");
	color(grisclaro);
	gotoxy(24,8);fgets(pproductos->nombre, 30, stdin);
	fflush(stdin);
	color(amarillo);
	gotoxy(24,10);printf("Valor del Producto");
	color(grisclaro);
	gotoxy(24,11);scanf("%f", &pproductos->valor);
	color(amarillo);
	gotoxy(24,13);printf("Cantidad del Producto");
	color(grisclaro);
	gotoxy(24,14);scanf("%d", &pproductos->cantidad);
	pproductos->vendida = 0;
	
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
	
	do{
		archivo = fopen("datos/productos.txt", "rb");
		fseek(archivo,sizeof(*pproductos)* ((*pUbicacion) - 1),SEEK_SET);
		fread(pproductos, sizeof(*pproductos), 1, archivo);
		color(amarillo);
		gotoxy(30,10);printf(" EDITAR PRODUCTO ");
		gotoxy(17,12);printf("1. Nombre ");
		gotoxy(17,13);printf("2. Valor ");
		gotoxy(17,14);printf("3. Cantidad ");
		gotoxy(17,15);printf("0. Salir");
		color(verde);
		gotoxy(17,17);printf(" Seleccione la opcion que desea Modificar: ");
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
				fclose(archivo);
				archivo = fopen("datos/productos.txt", "rb+");
				fseek(archivo,sizeof(*pproductos)* ((*pUbicacion) - 1),SEEK_SET);
				fwrite(pproductos,sizeof(*pproductos),1,archivo);
				fclose(archivo);
				break;
			}
			case 2:
			{
				color(verde);
				gotoxy(28,21);printf("Ingrese el nuevo valor: ");
				fflush(stdin);
				color(grisclaro);
				gotoxy(28,22);scanf("%f",&pproductos->valor);
				fclose(archivo);
				archivo = fopen("datos/productos.txt", "rb+");
				fseek(archivo,sizeof(*pproductos)* ((*pUbicacion) - 1),SEEK_SET);
				fwrite(pproductos,sizeof(*pproductos),1,archivo);
				fclose(archivo);
				break;
			}
			case 3:
			{
				color(verde);
				gotoxy(28,21);printf("Ingrese la nueva cantidad: ");
				fflush(stdin);
				color(grisclaro);
				gotoxy(28,22);scanf("%d", &pproductos->cantidad);
				fclose(archivo);
				archivo = fopen("datos/productos.txt", "rb+");
				fseek(archivo,sizeof(*pproductos)* ((*pUbicacion) - 1),SEEK_SET);
				fwrite(pproductos,sizeof(*pproductos),1,archivo);
				fclose(archivo);
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

void listar_productos(int y)
{
	FILE *archivo;
	int i = y;
	archivo = fopen("datos/productos.txt", "rb+");
	color(amarillo);
	while(fread(pproductos, sizeof(*pproductos), 1, archivo))
	{
		color(amarillo);
		dibujaRectangulo(30,i-1,48,i+1,'\372');
		color(grisclaro);
		gotoxy(32, i);printf("%d", pproductos->id);
		color(amarillo);
		gotoxy(35, i);printf("\263");
		color(grisclaro);
		gotoxy(36, i);printf("%s", pproductos->nombre);
		i += 2;
	}
	fclose(archivo);
}

bool datos_productos(int *pBuscar, Producto *producto)
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
			if(*pBuscar == pproductos->id)
			{
				strcpy(producto->nombre, pproductos->nombre);
				producto->valor = pproductos->valor;
				producto->cantidad = pproductos->cantidad;
				producto->vendida = pproductos->vendida;
				break;
			}
		}
		fclose(archivo);
	}
}

bool producto_cantidad(int *pUbicacion, int valor)
{
	FILE *archivo;
	archivo = fopen("datos/productos.txt", "rb");
	fseek(archivo,sizeof(*pproductos)* ((*pUbicacion) - 1),SEEK_SET);
	fread(pproductos, sizeof(*pproductos), 1, archivo);
	if(archivo == NULL)
	{
		return false;
	}
	pproductos->vendida = pproductos->vendida+valor;
	fclose(archivo);
	archivo = fopen("datos/productos.txt", "rb+");
	fseek(archivo,sizeof(*pproductos)* ((*pUbicacion) - 1),SEEK_SET);
	fwrite(pproductos,sizeof(*pproductos),1,archivo);
	fclose(archivo);
	return true;
}
