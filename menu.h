


void menu()
{
	//---------------------------------------------------------
	int opcion = 0, subOpcion = 0, buscar = 0, indice = 0, x = 0, y = 0;
	int* pOpcion = &opcion, *pSubOpcion = &subOpcion, *pBuscar = &buscar, *pIndice = &indice;
	char nombre[10] = "sebastian";
	FILE *archivo;
	
	printf("%d", sizeof(char[10]));
	
	do{
		system("mode con: cols=80 lines=26");
		system("cls");
		color(azul);
		dibujaRectangulo(1,1,79,24);
		color(verdeclaro);
		gotoxy(28,3);printf("Sistema de facturacion");
		
		color(rojoclaro);
		gotoxy(32,5);printf("Menu principal");
		
		color(cyan);
		gotoxy(33, 7);printf("1. Clientes");
		gotoxy(33, 8);printf("2. Productos");
		gotoxy(33, 9);printf("3. Facturas");
		gotoxy(33, 10);printf("0. Salir");
		color(verde);
		gotoxy(28, 12);printf("Ingrese la opcion: ");
		scanf("%d", &opcion);
		
		switch(*pOpcion)
		{
			case 1:
			{
				do{
					system("mode con: cols=80 lines=26");
					system("cls");
					color(azul);
					dibujaRectangulo(1,1,79,24);
					color(verdeclaro);
					gotoxy(28,3);printf("Sistema de facturacion");
					
					color(rojoclaro);
					gotoxy(35,5);printf("Clientes");
					
					color(cyan);
					gotoxy(30, 7);printf("1. Crear Cliente");
					gotoxy(30, 8);printf("2. Buscar Cliente");
					gotoxy(30, 9);printf("3. Editar Cliente");
					gotoxy(30, 10);printf("4. Mostrar Clientes");
					gotoxy(30, 11);printf("0. Salir");
					color(verde);
					gotoxy(28, 13);printf("Ingrese la opcion: ");
					scanf("%d", &subOpcion);
					
					switch(*pSubOpcion)
					{
						case 1:
						{
							system("cls");
							color(azul);
							dibujaRectangulo(1,1,79,24);
							crear_cliente();
							getch();
							break;
						};
						case 2:
						{
							gotoxy(20,16);printf("Ingrese el id del cliente a buscar ");
							scanf("%d", &buscar);
							system("cls");
							system("mode con: cols=92 lines=26");
							color(azul);
							dibujaRectangulo(1,1,91,24);
							*pIndice = buscar_cliente(pBuscar);
							if(*pIndice > 0)
							{
								cliente_encontrado(pIndice);
							}
							else
							{
								color(rojoclaro);
								gotoxy(24,12);printf("No se encontro ningun registro");
							}
							
							getch();
							break;
						};
						case 3:
						{
							system("cls");
							mostrar_clientes();
							int y = wherey();
							color(azul);
							dibujaRectangulo(1,1,91,y+1);
							color(verde);
							gotoxy(20,y+3);printf("Ingrese el id del cliente a editar ");
							scanf("%d", &buscar);
							system("mode con: cols=92 lines=26");
							color(azul);
							dibujaRectangulo(1,1,91,24);
							*pIndice = buscar_cliente(pBuscar);
							if(*pIndice > 0)
							{
								cliente_encontrado(pIndice);
								editar_cliente(pIndice);
							}
							else
							{
								color(rojoclaro);
								gotoxy(24,12);printf("No se encontro ningun registro");
							}
							
							break;
						};
						case 4:
						{
							mostrar_clientes();
							color(azul);
							dibujaRectangulo(1,1,91,wherey()+1);
							getch();
							break;
						};
					}
					
				} while(*pSubOpcion != 0);
				break;
			}
			case 2:
			{
				do{
					system("cls");
					dibujaRectangulo(1,1,80,24);
					color(verdeclaro);
					gotoxy(28,3);printf("Sistema de facturacion");
					
					color(rojoclaro);
					gotoxy(34,5);printf("Productos");
					
					color(cyan);
					gotoxy(17, 7);printf("1. Crear Producto");
					gotoxy(17, 8);printf("2. Buscar Producto");
					gotoxy(17, 9);printf("3. Editar Productos");
					gotoxy(17, 10);printf("4. Mostrar Productos");
					gotoxy(17, 11);printf("5. Listar Productos con la cantidad vendida");
					gotoxy(17, 12);printf("0. Salir");
					
					gotoxy(17, 14);printf("Ingrese la opcion: ");
					scanf("%d", &subOpcion);
					
					switch(*pSubOpcion)
					{
						case 1:
						{
							system("cls");
							color(azul);
							dibujaRectangulo(1,1,79,24);
							crear_productos();
							getch();
							break;
						};
						case 2:
						{
							gotoxy(20,16);printf("Ingrese el id del producto a buscar ");
							scanf("%d", &buscar);
							system("cls");
							color(azul);
							dibujaRectangulo(1,1,79,24);
							*pIndice = buscar_producto(pBuscar);
							if(*pIndice > 0)
							{
								producto_encontrado(pIndice);
							}
							else
							{
								color(rojoclaro);
								gotoxy(24,12);printf("No se encontro ningun registro");
							}
							
							getch();
							break;
						};
						case 3:
						{
							system("cls");
							mostrar_productos();
							int y = wherey();
							color(azul);
							dibujaRectangulo(1,1,79,y+1);
							color(verde);
							gotoxy(20,y+3);printf("Ingrese el id del producto a editar ");
							scanf("%d", &buscar);
							system("cls");
							color(azul);
							dibujaRectangulo(1,1,79,24);
							*pIndice = buscar_producto(pBuscar);
							if(*pIndice > 0)
							{
								producto_encontrado(pIndice);
								editar_producto(pIndice);
							}
							else
							{
								color(rojoclaro);
								gotoxy(24,12);printf("No se encontro ningun registro");
							}
							break;
						};
						case 4:
						{
							system("cls");
							mostrar_productos();
							color(azul);
							dibujaRectangulo(1,1,79,wherey()+2);
							getch();
							break;
						};
					}
					
				} while(*pSubOpcion != 0);
				break;
			}
			case 3:
			{
				do{
					system("cls");
					dibujaRectangulo(1,1,80,24);
					color(verdeclaro);
					gotoxy(28,3);printf("Sistema de facturacion");
					
					color(rojoclaro);
					gotoxy(35,5);printf("Facturas");
					
					color(cyan);
					gotoxy(27, 7);printf("1. Crear Factura");
					gotoxy(27, 8);printf("2. Buscar Factura");
					gotoxy(27, 9);printf("3. Editar Factura");
					gotoxy(27, 10);printf("4. Mostrar Facturas");
					gotoxy(27, 11);printf("5. Facturas por cliente");
					gotoxy(27, 12);printf("6. Facturas pagadas");
					gotoxy(27, 13);printf("7. Facturas sin pagar");
					gotoxy(27, 14);printf("0. Salir");
					
					gotoxy(27, 16);printf("Ingrese la opcion: ");
					scanf("%d", &subOpcion);
					
					switch(*pSubOpcion)
					{
						case 0:
						{
							
						};
						case 1:
						{
							system("mode con: cols=80 lines=70");
							crear_factura();
							getch();
							break;
						};
						case 2:
						{
							FILE *archivo;
							archivo = fopen("datos/factura.txt", "rb");
	
							if(archivo == NULL)
							{
								//return false;
							}
							rewind(archivo);
							fseek(archivo,ftell(archivo)-sizeof(*pFactura),SEEK_END);
							fread(pFactura, sizeof(*pFactura), 1, archivo);
							printf("%d \n", pFactura->cantidad[0]);
							printf("%d", pFactura->cantidad[1]);
							getch();
							break;
						};
						case 3:
						{
							mostrar_facturas();
							getch();
							break;
						};
						
					}
					
				} while(*pSubOpcion != 0);
				break;
			}
		}
		
		
	} while(*pOpcion != 0);
}
