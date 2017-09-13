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
	int cantidad = 0, product = 1, cantProducto = 0;
	int* pCantidad = &cantidad, *pProduct = &product, *pCantProducto = &cantProducto;
	char pagada;
	
	archivo = fopen("datos/factura.txt", "rb");
	
	if(archivo == NULL)
	{
		return false;
	}
	rewind(archivo);
	fseek(archivo,ftell(archivo)-sizeof(*pFactura),SEEK_END);
	fread(pFactura, sizeof(*pFactura), 1, archivo);
	pFactura->id = pFactura->id+1;
	fclose(archivo);
	color(amarillo);
	fflush(stdin);
	printf("Id del cliente: ");
	color(grisclaro);
	scanf("%d", &pFactura->cliente);
	if(buscar_cliente(&pFactura->cliente) == 0)
	{
		printf("El cliente no existe");
	}
	color(amarillo);
	fflush(stdin);
	printf("Ingrese los id de productos (0 - finaliza) \n");
	while(*pProduct != 0)
	{
		printf("Producto %d: ", *pCantidad+1);
		scanf("%d", pProduct);
		if(*pProduct > 0)
		{
			if(buscar_producto(pProduct) == 0)
			{
				printf("Producto no existe");
			}
			else
			{
				pFactura->producto[*pCantidad] = *pProduct;
				printf("Cantidad Producto %d: ", *pCantidad+1);
				scanf("%d", pCantProducto);
				pFactura->cantidad[*pCantidad] = *pCantProducto;
				archivo = fopen("datos/productos.txt", "rb");
				fseek(archivo,sizeof(*pproductos)* *pProduct,SEEK_SET);
				pFactura->total = pFactura->total + (pproductos->valor*pFactura->cantidad[*pCantidad]);
				(*pCantidad)++;
			}
		}
	}
	fflush(stdin);
	printf("Factura pagada S / N: ");
	scanf("%c", &pagada);
	if(pagada == 's')
	{
		pFactura->estado = true;
	}
	else
	{
		pFactura->estado = false;
	}
	/*color(grisclaro);
	fgets(pUsuario->nombre, 30, stdin);
	fflush(stdin);
	color(amarillo);
	fflush(stdin);
	printf("Direccion de cliente");
	color(grisclaro);
	fgets(pUsuario->direccion, 10, stdin);
	fflush(stdin);
	color(amarillo);
	fflush(stdin);
	printf("Telefono del cliente");
	color(grisclaro);
	fgets(pUsuario->telefono, 10, stdin);
	fflush(stdin);
	
	*/archivo = fopen("datos/factura.txt", "ab");
	
	if(archivo == NULL)
	{
		color(rojoclaro);
		printf("No se pudo guardar el registro");
	}
	else
	{
		fwrite(pFactura,sizeof(*pFactura),1,archivo);
		rewind(archivo);
		fclose(archivo);
		color(verdeclaro);
		printf("Registro Exitos");
	}
}

bool mostrar_facturas()
{
	FILE *archivo;
	int y = 7;
	
	archivo = fopen("datos/factura.txt", "rb");
	
	if(archivo == NULL)
	{
		return false;
	}
	else
	{
		system("mode con: cols=92 lines=50");
		gotoxy(35, 3);printf("Listado de clientes");
		//encabezado_tabla(5);
		while(fread(pFactura, sizeof(*pFactura), 1, archivo))
		{
			printf("id: %d \n", pFactura->id);
			printf("id: %d \n", pFactura->cliente);
			for(int i = 0; i< 2; i++)
			{
				printf("id: %d - %d \n", pFactura->producto[i], pFactura->cantidad[i]);
			}
			printf("id: %d \n", pFactura->total);
		}
	}
	fclose(archivo);
}

