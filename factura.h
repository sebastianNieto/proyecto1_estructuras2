struct Factura
{
	int id;
	int cliente;
	int producto[100];
	int cantidad[100];
	int total;
	bool estado;
}factura, *pFactura = &factura;

bool crear_factura()
{
	FILE *archivo;
	int cantidad = 0, product = 1, cantProducto = 0, y = 0, i=1, prValor = 0, prCantidad = 0, total = 0;
	int* pCantidad = &cantidad, *pProduct = &product, *pCantProducto = &cantProducto,*pPrValor = &prValor,*pPrCantidad = &prCantidad, *pTotal = &total;
	char pagada;
	bool bandera = false;
	
	archivo = fopen("datos/factura.txt", "rb");
	
	if(archivo == NULL)
	{
		return false;
	}
	rewind(archivo);
	fseek(archivo,ftell(archivo)-sizeof(*pFactura),SEEK_END);
	fread(pFactura, sizeof(*pFactura), 1, archivo);
	gotoxy(31, 2);printf("Seleccione Cliente");
	listar_cliente(3);
	pFactura->id = pFactura->id+1;
	fclose(archivo);
	color(amarillo);
	fflush(stdin);
	y = wherey();
	while(!bandera)
	{
		limpiaPantalla(29,y+2, 50, wherey()+4);
		color(amarillo);
		gotoxy(31, y+2);printf("Id del cliente: ");
		color(grisclaro);
		scanf("%d", &pFactura->cliente);
		if(buscar_cliente(&pFactura->cliente) == 0)
		{
			color(rojo);
			gotoxy(29, y+4);printf("El cliente no existe");
			getch();
		}
		else
		{
			limpiaPantalla(29,y+4, 50, wherey()+4);
			bandera = true;
		}
	}
	gotoxy(30, y+4);printf("Seleccione Productos");
	listar_productos(y+6);
	y = wherey();
	color(amarillo);
	fflush(stdin);
	gotoxy(18, y+2);printf("Ingrese los id de productos (0 - finaliza)");
	while(*pProduct != 0)
	{
		bandera = false;
		while(!bandera)
		{
			color(amarillo);
			gotoxy(32, y+i+3);printf("Producto %d: ", *pCantidad+1);
			color(grisclaro);
			scanf("%d", pProduct);
			if(*pProduct > 0)
			{
				if(buscar_producto(pProduct) == 0)
				{
					color(rojo);
					gotoxy(30, y+i+4);printf("Producto no existe");
					getch();
					limpiaPantalla(30,y+i+3,50,y+i+6);
				}
				else
				{
					i++;
					pFactura->producto[*pCantidad] = *pProduct;
					while(!bandera)
					{
						gotoxy(28, y+i+4);printf("Cantidad Producto %d: ", *pCantidad+1);
						scanf("%d", pCantProducto);
						
						datos_productos(pProduct, pPrValor, pPrCantidad);
						if(*pCantProducto > *pPrCantidad)
						{
							color(rojo);
							gotoxy(30, y+i+5);printf("Cantidad excedida");
							getch();
							printf("%d -- \n",y);
							limpiaPantalla(30,y+i+4,50,y+i+7);
						}
						else
						{
							pFactura->cantidad[*pCantidad] = *pCantProducto;
							
							*pTotal = *pTotal + (*pPrValor * pFactura->cantidad[*pCantidad]);
							(*pCantidad)++;
							i+=3;
							bandera = true;
						}
					}
				}
			}
			else
			{
				break;
			}
		}
	}
	pFactura->total = *pTotal;
	fflush(stdin);
	gotoxy(28, wherey()+2);printf("Factura pagada S / N: ");
	scanf("%c", &pagada);
	if(pagada == 's'|| pagada == 'S')
	{
		pFactura->estado = true;
	}
	else
	{
		pFactura->estado = false;
	}
	archivo = fopen("datos/factura.txt", "ab");
	
	if(archivo == NULL)
	{
		color(rojoclaro);
		gotoxy(24, wherey()+2);printf("No se pudo guardar el registro");
	}
	else
	{
		fwrite(pFactura,sizeof(*pFactura),1,archivo);
		rewind(archivo);
		fclose(archivo);
		color(verdeclaro);
		gotoxy(31, wherey()+2);printf("Registro Exitos");
	}
}


bool mostrar_facturas()
{
	FILE *archivo;
	int y = 7, id = 0, *pId = &id;
	Cliente cli, *pCli = &cli;
	
	archivo = fopen("datos/factura.txt", "rb");
	
	if(archivo == NULL)
	{
		return false;
	}
	else
	{
		system("mode con: cols=92 lines=50");
		gotoxy(35, 3);printf("Listado de Facturas");
		//encabezado_tabla(5);
		while(fread(pFactura, sizeof(*pFactura), 1, archivo))
		{
			*pId = pFactura->cliente;
			datos_cliente(pId, pCli);
			printf("id: %d \n", pFactura->id);
			printf("cedula: %s \n", pCli->cedula);
			printf("nombre: %s \n", pCli->nombre);
		}
	}
	fclose(archivo);
}

