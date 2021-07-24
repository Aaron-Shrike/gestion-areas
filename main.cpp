/*
	Gestion de areas
   	nombre, DNI jefe, lista de equipos
   	Gestionar equipo por area
   	tipo de equipos:proyector, pc, laptop y smart tv
      cada equipo tiene uan serie nombre, marca, año de compra
      	Proyector: lumenes
         Smart TV: tamaño y si es OLED
         Laptop: modelo, disco duro y si video es integrado
         PC: disco duro y RAM

   REPORTES:
   	1. Listado Areas
      2. Listado de equipos de Areas
      3. Estadistica de los tipos de equipos
      4. Dado un area mostrar las laptos a cargo
      5. Listado de equipos por tipo solicitado
      6. Cuantas laptops tienen video externo
*/

#include "basicas.CPP"

#define MAXDNI 9
#define DELTA 3

class Equipo{
  private:
 	char nombre[MAX];
   	char serie[MAX];
   	char marca[MAX];
   	int anio;
   	int tipo;

  public:
 	Equipo()
	{
   		this->nombre[0] = NULL;
      	this->serie[0] = NULL;
      	this->marca[0] = NULL;
      	this->anio = 0;
      	this->tipo = 0;
   	}

   	virtual void leer()
	{
   		cout << "Nombre : ", cin >> this->nombre;
      	cout << "Serie : ", cin >> this->serie;
      	cout << "Marca : ", cin >> this->marca;
      	this->anio = leeEntero("Anio de compra[1990-2017] : ",1990,2017,"Anio no valido");
      	this->tipo = getTipo();
   	}

   	void getNombre(char *nombreEquipo)
	{
   		strcpy(nombreEquipo,this->nombre);
   	}

   	void tipoEquipo(char *tipo)
	{
   		switch(this->tipo)
		{
      		case 1: strcpy(tipo,"Laptop"); break;
       		case 2: strcpy(tipo,"PC"); break;
         	case 3: strcpy(tipo,"Proyector"); break;
         	case 4: strcpy(tipo,"SmartTV"); break;
      	}
   	}

   virtual int getTipo() = 0;
   // 1:Laptop, 2:PC, 3:Proyector, 4:SmartTV
};

class Proyector:public Equipo{
  private:
 	int lumenes;

  public:
   	Proyector()
	{
   		this->lumenes = 0;
   	}

 	virtual void leer()
	{
      	cout << endl;
   		Equipo::leer();
      	cout << "Lumenes : "; cin >> this->lumenes;
   	}

   	virtual int getTipo()
	{
   		return 3;
   	}
};

class SmartTV:public Equipo{
  private:
 	int tamanio;
   	int oled;

  public:
   	SmartTV()
	{
   		this->tamanio = 0;
      	this->oled = 0;
   	}

 	virtual void leer()
	{
      	cout << endl;
   		Equipo::leer();
      	cout << "Tamanio : "; cin >> this->tamanio;
      	cout << " 1. OLED " << endl;
      	cout << " 2. Otra tecnologia" << endl;
      	this->oled = leeEntero("Tipo : ",1,2,"\t* No valido");
   	}

   	virtual int getTipo()
	{
   		return 4;
   	}
};

class PC:public Equipo{
  private:
 	int discoDuro;
   	int ram;
   	
  public:
   	PC()
	{
   		this->discoDuro = 0;
      	this->ram = 0;
   	}

 	virtual void leer()
	{
      	cout << endl;
   		Equipo::leer();
      	this->discoDuro = leeEntero("Disco Duro - Capacidad(GB)[100-2048] : ",100,2048,"\t* No valida");
      	this->ram = leeEntero("Tamanio de RAM(GB)[2-20] : ",2,20,"\t* No valida");
   	}

   	virtual int getTipo()
	{
   		return 2;
   	}

};

class Laptop:public Equipo{
  private:
 	char modelo[MAX];
   	int discoDuro;
   	int integrado;
   	
  public:
   	Laptop()
	{
   		this->modelo[0] = NULL;
      	this->discoDuro = 0;
      	this->integrado = 0;
   	}

 	virtual void leer()
	{
      	cout << endl;
   		Equipo::leer();
      	this->discoDuro = leeEntero("Disco Duro - Capacidad(GB)[100-2048] : ",100,2048,"\t* No valida");
      	cout << "Modelo : "; cin >> this->modelo;
      	cout << " 1. Video Integrado " << endl;
      	cout << " 2. Tarjeta de video " << endl;
      	this->integrado = leeEntero("Tipo de video : ",1,2,"\t* No valido");
   	}

   	int getIntegrado()
	{
   		return this->integrado;
   	}

   	virtual int getTipo()
	{
   		return 1;
   	}
};

class ListaEquipos{
  private:
 	int n;
   	int max;
   	Equipo **data; // no se puede poner:  Equipo *data[MAX];

 public:
 	ListaEquipos()
	{
   		this->n = 0;
      	this->max = 0;
      	this->data = NULL;
   	}
   	~ListaEquipos()
	{
   		if(this->max > 0)
		{
      		delete []this->data;
      	}
      	this->n = 0;
      	this->max = 0;
   	}

   	int getN()
	{
   		return this->n;
   	}

   	Equipo *get(int pos)
	{
  		return this->data[pos];
   	}

   	void agregar(Equipo *equipo)
	{
   		if(this->n == this->max)
		{
      		this->crecer();
      	}
      	this->data[this->n] = equipo;
      	this->n++;
   	}

 private:
 	void crecer()
	{
   		Equipo **aux;

      	this->max += DELTA;
      	aux = new Equipo *[this->max];

      	for(int i=0;i<this->n;i++)
		{
      		aux[i] = this->data[i];
      	}
      	if(this->n >0)
		{
      		delete []this->data;
      	}
      	this->data = aux;
   	}
};

class Area{
  private:
 	char nombreArea[MAX];
   	char DNIJefe[MAXDNI];
   	ListaEquipos equipos;

  public:
   	Area()
	{
   		this->nombreArea[0] = NULL;
      	this->DNIJefe[0] = NULL;
   	}

 	void leer()
	{
   		cout << "Nombre del Area : "; cin >> this->nombreArea;
      	cout << "DNI del Jefe : "; cin >> this->DNIJefe;
   	}

   	void getNombre(char *nombre)
	{
   		strcpy(nombre,this->nombreArea);
   	}

   	void getDNI(char *dni)
	{
   		strcpy(dni,this->DNIJefe);
   	}

   	ListaEquipos &getListaEquipos()
	{
   		return this->equipos;
   	}

//Funciones de ListaEquipo
   	int getCantidadEquipos()
	{
   		return this->equipos.getN();
   	}

   	void agregarEquipo(Equipo *eq)
	{
   		this->equipos.agregar(eq);
   	}

   	char getNombreEquipo(int pos,char *aux)
	{
   		this->equipos.get(pos)->getNombre(aux);

      	return *aux;
   	}

   	char getTipoEquipoNombre(int pos,char *aux)
	{
   		this->equipos.get(pos)->tipoEquipo(aux);

      	return *aux;
   	}

   	int getTipoEquipoNumero(int pos)
	{
   		return this->equipos.get(pos)->getTipo();
   	}

   	int getVideoNumero(int pos)
	{
   		return ((Laptop *)this->equipos.get(pos))->getIntegrado();
   	}
};

class NodoArea{
  friend class ListaAreas;
  
  private:
 	Area area;
   	NodoArea *sgte;

  public:
 	NodoArea()
	{
   		this->sgte = NULL;
   	}
};

class ListaAreas{
  private:
   	int n;
 	NodoArea *cab;

  public:
 	ListaAreas()
	{
   		this->n =0;
      	this->cab = NULL;
   	}
   	~ListaAreas()
	{
   		NodoArea *temp = this->cab;

      	while(temp != NULL)
		{
         	this->cab = temp->sgte;
         	delete temp;
         	temp = this->cab;
      	}
      	this->n = 0;
   	}

   	void agregar(Area &nueva)
	{
   		NodoArea *temp = new NodoArea();
      	NodoArea *ultimo;

      	temp->area = nueva;

      	if(this->cab == NULL)
		{
      		this->cab = temp;
      	}
		else
		{
      		ultimo = this->cab;
         	while(ultimo->sgte != NULL)
			{
         		ultimo = ultimo->sgte;
         	}
         	ultimo->sgte = temp;
      	}
      	this->n++;
   	}

   	int getN()
   	{
   		return this->n;
   	}

   	Area *get(int pos)
	{
   		NodoArea *temp = this->cab;
      	Area *aux = NULL;

      	if(pos>=0 && pos<this->n)
		{
      		for(int i=0;i<pos;i++)
			{
         		temp = temp->sgte;
         	}
         	aux = &(temp->area);

         	return aux;
      	}
		else
		{
      		return NULL;
      	}
   	}

   	Area *buscarAreaPorDNI(char *DNIBuscar)
	{
   		NodoArea *temp = this->cab;
      	char DNI[MAXDNI];

      	while(temp != NULL)
		{
         	temp->area.getDNI(DNI);

         	if(strcmpi(DNI,DNIBuscar)==0)
			{
         		return &(temp->area);
         	}

         	temp = temp->sgte;
      	}

      	return NULL;
   	}
};


ListaAreas empresa;

// LISTA DE MENU
int leerOpcion()
{
	char *opciones[4]={"Registrar area","Registrar equipo","Reportes","Salir"};
   	int op;

   	for(int i=0;i<4;i++)
	{
   		cout<<(i+1)<<".- "<<opciones[i]<<endl;
   	}

	op=leeEntero(" Opcion: ",1,4,"\t* Opcion no valida");

   	return op;
}

int leerReporte()
{
	char *reportes[7]={"Listar areas","Listar equipos de areas","Estadistica por tipo de equipo",
   		"Dado un area mostrar las laptos a cargo","Listado de equipos por tipo solicitado",
        "Cuantas laptops tienen video externo","Retornar"};
   	int rep;

   	for(int i=0;i<7;i++)
	{
   		cout<<(i+1)<<".- "<<reportes[i]<<endl;
   	}

	rep=leeEntero(" Opcion: ",1,7,"\t* Opcion no valida");

   	return rep;
}

//EQUIPO
int leerTipoEquipo()
{
	char *tipos[4]={"Laptop","PC","Proyector","SmartTV"};
   	int tipo;

   	cout << endl;
   	for(int i=0;i<4;i++)
	{
   		cout << " " << (i+1) << ". "<< tipos[i] << endl;
   	}

   	tipo=leeEntero("Tipo de equipo: ",1,4,"\t* Tipo no valida");

   	return tipo;
}

Equipo *crearEquipo(int tipo)
{
	Equipo *e;

   	switch(tipo)
	{
   		case 1: e = new Laptop(); break;
      	case 2: e = new PC(); break;
      	case 3: e = new Proyector(); break;
      	case 4: e = new SmartTV(); break;
   	}

   return e;
}

//OTROS
void tipoEquipoGeneral(char *tipo,int num)
{
	switch(num+1)
	{
   		case 1: strcpy(tipo,"Laptop"); break;
      	case 2: strcpy(tipo,"PC"); break;
      	case 3: strcpy(tipo,"Proyector"); break;
      	case 4: strcpy(tipo,"SmartTV"); break;
	}
}

void tipoVideoGeneral(char *video,int num)
{
	switch(num+1)
	{
   		case 1: strcpy(video,"Video Integrado"); break;
      	case 2: strcpy(video,"Tarjeta de video"); break;
	}
}

//REPORTES

// Reporte N01: "Listar areas"
void listarAreas()
{
   	char nombre[MAX];
   	char DNI[MAXDNI];
   	int numEquipos;

   	Area *area;

   	//mostrar nombre, dni y numero de equipos
   	cout << endl;
   	cout<<"--------- Listado de Areas ---------"<<endl;
   	for(int i=0;i<empresa.getN();i++)
	{
      	area = empresa.get(i);

      	area->getDNI(DNI);
      	area->getNombre(nombre);
      	numEquipos = area->getCantidadEquipos();

      	cout << endl;
      	cout<<(i+1)<<".- "<<nombre<<" - "<<DNI<<" - " <<numEquipos<<endl;
   	}

   	cout << endl;
   	cout<<"------------------------------------"<<endl;
	getch();
}

// Reporte N02: "Listar equipos de areas"
void listarEquiposDeAreas()
{
	char nombreArea[MAX];
   	char nombreEquipo[MAX];
   	char nombreTipo[MAX];
   	int n;

   	Area *area;

   	cout << endl;
   	cout<<"---------- Equipos de Areas ----------"<<endl;
   	for(int i=0;i<empresa.getN();i++)
	{
      	area = empresa.get(i);

      	area->getNombre(nombreArea);

      	cout << endl;
      	cout<< "Area N" <<(i+1)<< ": " <<nombreArea<<endl;

      	n=0;
      	cout << endl;
      	for(int j=0;j<area->getCantidadEquipos();j++)
		{
         	area->getNombreEquipo(j,nombreEquipo);
         	area->getTipoEquipoNombre(j,nombreTipo);

      		cout << "   " <<(n+1)<< ". " <<nombreEquipo<< " (" <<nombreTipo<< ")" << endl;
         	n++;
   		}
   	}

   	cout << endl;
   	cout<<"--------------------------------------"<<endl;
	getch();
}

// Reprote N03: "Estadistica por tipo de equipo"
void estadisticaTipoEquipo()
{
   	char nombreTipo[MAX];
   	int contador[4] = {0,0,0,0};

   	Area *area;

   	cout << endl;
   	cout<<"---- Estadistica de los Tipo de Equipos ----"<<endl;
   	for(int k=0;k<4;k++)
	{
   		for(int i=0;i<empresa.getN();i++)
		{
         	area = empresa.get(i);

      		for(int j=0;j<area->getCantidadEquipos();j++)
			{
         		if(area->getTipoEquipoNumero(j) - 1 == k)
				{
         			contador[k]++;
         		}
   			}
   		}
   	}

   	for(int k=0;k<4;k++)
	{
   		tipoEquipoGeneral(nombreTipo,k);

      	cout << endl;
   		cout << (k+1) << ".- " << nombreTipo << ": " << contador[k] << endl;
   	}

   	cout << endl;
   	cout<<"--------------------------------------------"<<endl;
	getch();
}

// Reporte N04: "Dado un area mostrar las laptos a cargo"
void dadaAreaListarLaptops()
{
	char nombreArea[MAX];
   	char nombreEquipo[MAX];
   	int posArea;
   	int flag = 0;
   	int n = 0;

   	Area *area;

   	cout << endl;
   	cout<<"------- Areas -------"<<endl;
   	for(int i=0;i<empresa.getN();i++)
	{
      	empresa.get(i)->getNombre(nombreArea);

      	cout<<(i+1)<< ". " << nombreArea <<endl;
   	}

	posArea = leeEntero(" Opcion: ",1,empresa.getN(),"\t* Opcion no valida");

   	area = empresa.get(posArea-1);

   	area->getNombre(nombreArea);

   	cout << endl;
   	cout<<"---------- LAPTOPS (" << nombreArea << ") ----------"<<endl;
   	cout << endl;

   	for(int j=0;j<area->getCantidadEquipos();j++)
	{
   		if(area->getTipoEquipoNumero(j) == 1)
		{
   			area->getNombreEquipo(j,nombreEquipo);

         	flag = 1;
      		cout << "  " <<(n+1)<< ". " << nombreEquipo << endl;
      		n++;
      	}
   	}

   	if(flag == 0)
	{
   		cout << "\t* No hay laptops registradas en esta area*" << endl;
   	}

   	cout << endl;
   	cout<<"----------------------------------------------------"<<endl;
	getch();
}

// Reporte N05: "Listado de equipos por tipo solicitado"
void dadoTipoListarEquipos()
{
	char nombreTipo[MAX];
   	char nombreEquipo[MAX];
   	int tipo;
   	int flag = 0;
   	int n = 0;

   	Area *area;

   	cout << endl;
   	tipo = leerTipoEquipo();
   	tipoEquipoGeneral(nombreTipo,tipo-1);

   	cout << endl;
   	cout<<"---------- LISTADO DE EQUIPO (" << nombreTipo << ") ----------"<<endl;
   	cout << endl;

   	for(int i=0;i<empresa.getN();i++)
	{
   		area = empresa.get(i);

   		for(int j=0;j<area->getCantidadEquipos();j++)
		{
	   		if(area->getTipoEquipoNumero(j) == tipo)
			{
	   			area->getNombreEquipo(j,nombreEquipo);
	
	         	flag = 1;
	      		cout << "  " <<(n+1)<< ". " << nombreEquipo << endl;
	      		n++;
	      	}
   		}
   	}

   	if(flag == 0)
	{
   		cout << "\t* No hay " << nombreTipo << " registradas(os)*" << endl;
   	}

   	cout << endl;
   	cout<<"--------------------------------------------------------------"<<endl;
	getch();
}

// Reporte N06: "Cuantas laptops tienen video externo"
void cantidadLaptopsVideoExterno()
{
	char nombreTipo[MAX];
   	int contador[2] = {0,0};

   	Area *area;

   	cout << endl;
   	cout<<"---- LAPTOPS CON TARJETA DE VIDEO EXTERNO ----"<<endl;
   	for(int i=0;i<empresa.getN();i++)
	{
   		area = empresa.get(i);

      	for(int j=0;j<area->getCantidadEquipos();j++)
		{
      		if(area->getTipoEquipoNumero(j) - 1 == 1/*1: laptop*/)
			{
         		if(area->getVideoNumero(j) == 1)
				{
            		contador[0]++;
            	}
            	if(area->getVideoNumero(j) == 2)
				{
            		contador[1]++;
            	}
         	}
   		}
   	}

   	cout << endl;
   	cout << "  Tarejeta de video: " << contador[1] << endl;

   /*for(int k=0;k<2;k++){
   	tipoVideoGeneral(nombreTipo,k);

      cout << endl;
   	cout << (k+1) << ".- " << nombreTipo << ": " << contador[k] << endl;
   }*/

   	cout << endl;
   	cout<<"--------------------------------------------"<<endl;
	getch();
}

//MENU

// Enlazada de dinamica
void registrarArea()
{
	Area area;

   	cout << endl;
   	area.leer();
   	empresa.agregar(area);

   	cout << endl;
   	cout << "\t* Area registrada exitosamente*" << endl;
   	getch();
}

/*
// Dinamica de enlazada,
void registrarArea(){
	Area *area;

   cout << endl;
   area->leer();
   empresa.agregar(area);

   cout << endl;
   cout << " *Area registrada exitosamente*" << endl;
   getch();
}
*/

void registrarEquipo()
{
   	char nombre[MAX];
   	int op;
   	int tipo;

   	Area *area;
   	Equipo *equipo;

   	cout << endl;
   	cout<<"------- Areas -------"<<endl;
   	for(int i=0;i<empresa.getN();i++)
	{
      	empresa.get(i)->getNombre(nombre);

      	cout<<(i+1)<<". "<<nombre<<endl;
   	}

	op = leeEntero(" Opcion: ",1,empresa.getN(),"\t* Opcion no valida");

   	area = empresa.get(op-1);

   	if(area != NULL )
	{
   		tipo = leerTipoEquipo();
      	equipo = crearEquipo(tipo);
      	equipo->leer();
      	area->agregarEquipo(equipo);

      	cout << endl;
      	cout << "\t* El equipo se registro exitosamente*" << endl;
   	}
	else
	{
   		cout << "\t* No se encontro el area solicitada" << endl;
   	}
   	getch();
}

void presentarReportes()
{
  	int rep;

	do
	{
      	system("cls");
  		cout<<"----------------- REPORTES -----------------"<<endl;
  		rep=leerReporte();
   		switch(rep)
		{
   			case 1: listarAreas(); break;
      		case 2: listarEquiposDeAreas(); break;
      		case 3: estadisticaTipoEquipo(); break;
         	case 4: dadaAreaListarLaptops(); break;
      		case 5: dadoTipoListarEquipos(); break;
         	case 6: cantidadLaptopsVideoExterno(); break;
         	case 7:break;
   		}
  	}while(rep<7);
}

int main()
{
  	int op;

	do
	{
  		system("cls");
  		cout<<"------------ MENU ------------"<<endl;
  		op=leerOpcion();
   		switch(op)
		{
   			case 1: registrarArea(); break;
      		case 2: registrarEquipo(); break;
      		case 3: presentarReportes(); break;
      		case 4: break;
   		}
  	}while(op<4);
}
