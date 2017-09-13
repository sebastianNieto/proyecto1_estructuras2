struct Cliente
{
	int id;
	char cedula[10];
	char nombre[30];
	char direccion[30];
	char telefono[10];
} usuario, copiaUsuario, *pUsuario = &usuario, *pCopiaUsuario = &copiaUsuario;

bool crear_cliente()
{
	FILE *archivo;
	
	archivo = fopen("datos/clientes.txt", "rb");
	
	if(archivo == NULL)
	{
		return false;
	}
	rewind(archivo);
	fseek(archivo,ftell(archivo)-sizeof(*pUsuario),SEEK_END);
	fread(pUsuario, sizeof(*pUsuario), 1, archivo);
	pUsuario->id = pUsuario->id+1;
	fclose(archivo);
	color(amarillo);
	fflush(stdin);
	gotoxy(24,4);printf("Numero de cedula del cliente");
	color(grisclaro);
	gotoxy(24,5);fgets(pUsuario->cedula, 10, stdin);
	color(amarillo);
	fflush(stdin);
	gotoxy(24,7);printf("Nombre del cliente");
	color(grisclaro);
	gotoxy(24,8);fgets(pUsuario->nombre, 30, stdin);
	fflush(stdin);
	color(amarillo);
	fflush(stdin);
	gotoxy(24,10);printf("Direccion de cliente");
	color(grisclaro);
	gotoxy(24,11);fgets(pUsuario->direccion, 10, stdin);
	fflush(stdin);
	color(amarillo);
	fflush(stdin);
	gotoxy(24,13);printf("Telefono del cliente");
	color(grisclaro);
	gotoxy(24,14);fgets(pUsuario->telefono, 10, stdin);
	fflush(stdin);
	
	archivo = fopen("datos/clientes.txt", "ab");
	
	if(archivo == NULL)
	{
		color(rojoclaro);
		gotoxy(24, 16);printf("No se pudo guardar el registro");
	}
	else
	{
		fwrite(pUsuario,sizeof(*pUsuario),1,archivo);
		rewind(archivo);
		fclose(archivo);
		color(verdeclaro);
		gotoxy(32, 16);printf("Registro Exitos");
	}
}

void encabezado_tabla(int y)
{
	color(amarillo);
	dibujaRectangulo(2,y-1,90,y+1,'\372');
	color(azulclaro);
	gotoxy(3, y);printf("Id");
	color(amarillo);
	gotoxy(6, y);printf("\263");
	color(azulclaro);
	gotoxy(7, y);printf("Cedula");
	color(amarillo);
	gotoxy(17, y);printf("\263");
	color(azulclaro);
	gotoxy(18, y);printf("Nombre");
	color(amarillo);
	gotoxy(48, y);printf("\263");
	color(azulclaro);
	gotoxy(49, y);printf("Direccion");
	color(amarillo);
	gotoxy(79, y);printf("\263");
	color(azulclaro);
	gotoxy(80, y);printf("Telefono");
}

void cuerpo_tabla(Cliente *pUsuario, int y)
{
	
	color(amarillo);
	dibujaRectangulo(2,y-1,90,y+1,'\372');
	color(grisclaro);
	gotoxy(3, y);printf("%d", pUsuario->id);
	color(amarillo);
	gotoxy(6, y);printf("\263");
	color(grisclaro);
	gotoxy(7, y);printf("%s", pUsuario->cedula);
	color(amarillo);
	gotoxy(17, y);printf("\263");
	color(grisclaro);
	gotoxy(18, y);printf("%s", pUsuario->nombre);
	color(amarillo);
	gotoxy(48, y);printf("\263");
	color(grisclaro);
	gotoxy(49, y);printf("%s", pUsuario->direccion);
	color(amarillo);
	gotoxy(79, y);printf("\263");
	color(grisclaro);
	gotoxy(80, y);printf("%s", pUsuario->telefono);
}

bool mostrar_clientes()
{
	FILE *archivo;
	int y = 7;
	
	archivo = fopen("datos/clientes.txt", "rb");
	
	if(archivo == NULL)
	{
		return false;
	}
	else
	{
		system("mode con: cols=92 lines=50");
		gotoxy(35, 3);printf("Listado de clientes");
		encabezado_tabla(5);
		while(fread(pUsuario, sizeof(*pUsuario), 1, archivo))
		{
			cuerpo_tabla(pUsuario, y);
			y+=2;
		}
	}
	fclose(archivo);
}

void cliente_encontrado(int *pIndice)
{
	FILE *archivo;
	
	color(verdeclaro);
	gotoxy(35, 3);printf("Registro Encontrado");
	archivo = fopen("datos/clientes.txt", "rb");
	fseek(archivo,sizeof(*pUsuario)* *pIndice,SEEK_SET);
	encabezado_tabla(5);
	cuerpo_tabla(pUsuario, 7);
	fclose(archivo);
}

int buscar_cliente(int *pBuscar)
{
	FILE *archivo;
	int indice = 0, *pIndice = &indice;
	bool bandera = false, *pBandera = &bandera;
	archivo = fopen("datos/clientes.txt", "rb");
	
	if(archivo == NULL)
	{
		return false;
	}
	else
	{
		while(fread(pUsuario, sizeof(*pUsuario), 1, archivo))
		{
			(*pIndice)++;
			if(*pBuscar == pUsuario->id)
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

void editar_cliente(int *pUbicacion)
{
	int opcion = 0, *pOpcion = &opcion;
	
	FILE *archivo;
	archivo = fopen("datos/clientes.txt", "rb+");
	fseek(archivo,sizeof(*pUsuario)* ((*pUbicacion) - 1),SEEK_SET);
	
	do{
		color(amarillo);
		gotoxy(33,10);printf("Escoge el campo a editar");
		color(grisclaro);
		gotoxy(33,12);printf("1: Cedula");
		gotoxy(33,13);printf("2: Nombre");
		gotoxy(33,14);printf("3: Direccion");
		gotoxy(33,15);printf("4: Telefono");
		gotoxy(33,17);printf("0: Cancelar");
		color(verde);
		gotoxy(33,19);printf("Ingresa la opcion: ");
		color(grisclaro);
		scanf("%d", &opcion);
		switch(opcion)
		{
			case 1:
			{
				color(verde);
				gotoxy(28,21);printf("Ingrese el nuevo numero de cedula: ");
				fflush(stdin);
				color(grisclaro);
				gotoxy(28,22);fgets(pUsuario->cedula, 10, stdin);
				fwrite(pUsuario,sizeof(*pUsuario),1,archivo);
				break;
			}
			case 2:
			{
				color(verde);
				gotoxy(33,21);printf("Ingrese el nuevo nombre: ");
				fflush(stdin);
				color(grisclaro);
				gotoxy(33,22);fgets(pUsuario->nombre, 30, stdin);
				fwrite(pUsuario,sizeof(*pUsuario),1,archivo);
				break;
			}
			case 3:
			{
				color(verde);
				gotoxy(31,21);printf("Ingrese la nueva direccion: ");
				fflush(stdin);
				color(grisclaro);
				gotoxy(31,22);fgets(pUsuario->direccion, 30, stdin);
				fwrite(pUsuario,sizeof(*pUsuario),1,archivo);
				break;
			}
			case 4:
			{
				color(verde);
				gotoxy(27,21);printf("Ingrese el nuevo numero de telefono: ");
				fflush(stdin);
				color(grisclaro);
				gotoxy(27,22);fgets(pUsuario->telefono, 10, stdin);
				fwrite(pUsuario,sizeof(*pUsuario),1,archivo);
				break;
			}
		}
		if(*pOpcion != 0)
		{
			system("cls");
			cliente_encontrado(pUbicacion);
		}
	} while(*pOpcion != 0);
	
	fclose(archivo);
}

void listar_cliente(int y)
{
	FILE *archivo;
	int i = y;
	archivo = fopen("datos/clientes.txt", "rb+");
	while(fread(pUsuario, sizeof(*pUsuario), 1, archivo))
	{
		color(amarillo);
		dibujaRectangulo(30,i,48,i+2,'\372');
		color(grisclaro);
		gotoxy(32, i+1);printf("%d", pUsuario->id);
		color(amarillo);
		gotoxy(35, i+1);printf("\263");
		color(grisclaro);
		gotoxy(36, i+1);printf("%s", pUsuario->nombre);
		i += 2;
	}
	fclose(archivo);
}

bool datos_cliente(int *pBuscar, Cliente *cliente)
{
	FILE *archivo;
	int indice = 0, *pIndice = &indice;
	bool bandera = false, *pBandera = &bandera;
	
	archivo = fopen("datos/clientes.txt", "rb");
	
	if(archivo == NULL)
	{
		return false;
	}
	else
	{
		while(fread(pUsuario, sizeof(*pUsuario), 1, archivo))
		{
			if(*pBuscar == pUsuario->id)
			{
				strcpy(cliente->cedula, pUsuario->cedula);
				strcpy(cliente->nombre, pUsuario->nombre);
				break;
			}
		}
		fclose(archivo);
	}
}

