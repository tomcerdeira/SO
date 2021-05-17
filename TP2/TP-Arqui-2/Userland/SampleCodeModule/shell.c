#include <shell.h>

static char user[20] = {0};
static char userShell[30] = {0};

static int isInitialized = 0;


void init()
{
  // if (isInitialized)
  // {
  //   shell();
  // }
  isInitialized = 1;
  setFontColor(MODULE_COLOR);
  printf("TP-SO 2021 V1\n");
  setFontColor(DEFAULT_FONT_COLOR);
  printf("Por favor, ingrese un nombre de usuario: ");
  scanf("%s", user);
  printf("Hola ");
  setFontColor(USER_COLOR);
  printf("%s", user);
  setFontColor(DEFAULT_FONT_COLOR);
  printf("! Para mas informacion ingrese el comando ");
  setFontColor(MODULE_COLOR);
  printf("\"help\"\n");
  setFontColor(DEFAULT_FONT_COLOR);
  int i = 0;
  for (; user[i] != 0; i++)
  {
    userShell[i] = user[i];
  }
  userShell[i++] = ':';
  userShell[i++] = '$';
  userShell[i] = '>';
  printf("\n");
  shellHandler();
}

void shellHandler()
{
  int exit = 0;
  char buff[100] = {0};

  while (!exit)
  {

    setFontColor(USER_COLOR);
    printf("%s", userShell);
    setFontColor(DEFAULT_FONT_COLOR);

    char param1[100] = {0};
    char param2[100] = {0};

    scanf("%s %s %s", buff, param1,param2);

    if (strcmp(buff, "help"))
    {
      printf("\n");
      setFontColor(MODULE_COLOR);
      printf("help: ");
      setFontColor(DEFAULT_FONT_COLOR);
      printf("Muestra los distintos modulos disponibles y una descripcion de su uso.\n");
      printf("\n");
      setFontColor(MODULE_COLOR);
      printf("printmem: ");
      setFontColor(DEFAULT_FONT_COLOR);
      printf("Recibe como argumento un puntero y realiza un volcado de memoria de 32 bytes a partir de ella.\n");
      printf("\n");
      setFontColor(MODULE_COLOR);
      printf("inforeg: ");
      setFontColor(DEFAULT_FONT_COLOR);
      printf("Imprime en pantalla el valor de todos los registros.\n");
      printf("Se debe apretar la tecla ");
      setFontColor(MODULE_COLOR);
      printf("SHIFT");
      setFontColor(DEFAULT_FONT_COLOR);
      printf(" antes de invocar el modulo para sacar un snapshot los valores actuales de los registros.\n");
      printf("\n");
      setFontColor(MODULE_COLOR);
      printf("time: ");
      setFontColor(DEFAULT_FONT_COLOR);
      printf("Despliega el dia y la hora del sistema.\n");
      printf("\n");
      //setFontColor(MODULE_COLOR);
      //printf("chess: ");
      //setFontColor(DEFAULT_FONT_COLOR);
      //printf("Despliega un juego de ajedrez en formato grafico.\n");
      //printf("\n");
      setFontColor(MODULE_COLOR);
      printf("ps: ");
      setFontColor(DEFAULT_FONT_COLOR);
      printf("Imprime la lista de todos los procesos con sus propiedades: PID, prioridad, nombre, stack y estado.\n");
      printf("\n");
      setFontColor(MODULE_COLOR);
      printf("loop: ");
      setFontColor(DEFAULT_FONT_COLOR);
      printf("Imprime constantemente su PID.\n");
      printf("\n");
      setFontColor(MODULE_COLOR);
      printf("kill (PID): ");
      setFontColor(DEFAULT_FONT_COLOR);
      printf("Dado un PID, mata al proceso.\n");
      printf("\n");
      setFontColor(MODULE_COLOR);
      printf("nice (PID, Prio): ");
      setFontColor(DEFAULT_FONT_COLOR);
      printf("Dado un PID, le asigna una nueva prioridad Prio al proceso.\n");
      printf("\n");
      setFontColor(MODULE_COLOR);
      printf("block (PID): ");
      setFontColor(DEFAULT_FONT_COLOR);
      printf("Dado un PID, bloquea al proceso.\n");
      printf("\n");
      setFontColor(MODULE_COLOR);
      printf("cat: ");
      setFontColor(DEFAULT_FONT_COLOR);
      printf("Imprime el stdin tal como lo recibe.\n");
      printf("\n");
      setFontColor(MODULE_COLOR);
      printf("testnosync: ");
      setFontColor(DEFAULT_FONT_COLOR);
      printf("Ejecuta el test de sincronismo sin semaforos.\n");
      printf("\n");
      setFontColor(MODULE_COLOR);
      printf("testsync: ");
      setFontColor(DEFAULT_FONT_COLOR);
      printf("Ejecuta el test de sincronismo con semaforos.\n");
      printf("\n");
      //
      setFontColor(ERROR_COLOR);
      printf("exceptionZero: ");
      setFontColor(DEFAULT_FONT_COLOR);
      printf("Demostracion de excepcion de tipo division por cero.\n");
      printf("\n");
      setFontColor(ERROR_COLOR);
      printf("exceptionOpCode: ");
      setFontColor(DEFAULT_FONT_COLOR);
      printf("Demostracion de excepcion de tipo opcode invalido.\n");
      printf("\n");
      setFontColor(MODULE_COLOR);
      printf("exit: ");
      setFontColor(DEFAULT_FONT_COLOR);
      printf("Salir del programa.\n");
      printf("\n");
    }
    else if (strcmp(buff, "printmem"))
    {
      printf("\n");
      createProcess("printMem", &printmem, strToInt(param1), 0);
      // printmem(strToInt(param1));
      printf("\n");
    }
    else if (strcmp(buff, "inforeg"))
    {

      printf("\n");

      char *registers[] = {
          "R15: ", "R14: ", "R13: ", "R12: ", "R11: ",
          "R10: ", "R9: ", "R8: ", "RSI: ", "RDI: ",
          "RBP: ", "RDX: ", "RCX: ", "RBX: ", "RAX: ",
          "RIP: ", "CS:  ", "FLAGS: ", "RSP: "};

      int cant_registers = 19;

      uint64_t buffer[25] = {0};
      getRegisterState((int *)buffer);
      for (int i = 0; i < cant_registers; i++)
      {
        setFontColor(0x098DBA);
        printf("%s", registers[i]);
        setFontColor(DEFAULT_FONT_COLOR);
        printf("0x");
        printBase(buffer[i], 16);
        printf("\n");
      }
      printf("\n");
    }
    else if (strcmp(buff, "time"))
    {
      printf("\n");
      createProcess("time", &printTime, 0, 0);

      printf("\n");
    }
    else if (strcmp(buff, "chess"))
    {
      //printf("CHESS");
      initChess();
      clearConsoleIn(0);
    }
    else if (strcmp(buff, "clear"))
    {
      clearConsoleIn(0);
    }
    else if (strcmp(buff, "exceptionZero"))
    {
      printf("\n");
      int i = 1 / 0;
    }
    else if (strcmp(buff, "exceptionOpCode"))
    {
      printf("\n");
      _opCodeException();
    }
    else if (strcmp(buff, "loop"))
    {
      createProcess("loop", &endless_loop, 0, 0);     
    }
    else if (strcmp(buff, "ps"))
    {
      char buffer[1024]={0};
      ps(buffer);
     printf(buffer);
     
    }
    else if(strcmp(buff,"block"))
    {
      block(strToInt(param1));
    }
    else if(strcmp(buff,"nice")){
      nice(strToInt(param1),strToInt(param2));
    }

    else if (strcmp(buff, "exit"))
    {
      exit = 1;
    }
    else if (strcmp(buff, "testsync"))
    {
      test_sync();
    }
    else if (strcmp(buff, "testnosync"))
    {
      test_no_sync();
    }
        else if (strcmp(buff, "cat"))
    {
      cat();
    }
     else if (strcmp(buff, "testprocesses"))
    {
      test_processes();
    }
    //TODO agregar:
    // - help --> falta agregar todas las syscalls nuevas (los tests)
    // - MEM --> falta hacerla syscall
    // - PS --> hacerlo más lindo
    // - LOOP (id) --> hacerlo más lindo
    // - Kill (id) --> falta hacerla syscall
    // - Nice (id np) --> Listo
    // - Block (id) --> listo
    // - Sem --> Imprime la lista de todos los semaforos con sus propiedades (ya funcionan los semáforos)
    // - Cat (stdin) --> Imprime el stdin pasado como param
    // - WC (input)--> Cuenta la cantidad de lineas del input
    // - Filter (input) --> Filtra las vocales del input
    // - Pipe --> Imprime la lista de todos los pipes con sus propiedades
    // - Phylo --> Implementar el problema de los filosofos
    // Implementar forground y background
    else
    {
      printf("\n");
      error("Invalid OpCode: \"%s\" not recognized as a command\n", buff);
      printf("\n");
    }
  }

  clearConsoleIn(0);
  printf("Usted ha utilizado un simple SO implentado por: \n Tomas Cerdeira - 60051 \n Santiago Garcia Montager - 60352 \n Lucas Catolino - 61817 \n Esperamos que le haya gustado \n");
  printf("Mayo 2021");
}

void shellManager()
{
  setFontColor(DEFAULT_FONT_COLOR);
  setBackGroundColor(DEFAULT_BACKGROUND_COLOR);
  init();
}

void endless_loop()
{
  while (1)
  {
    printf("%d ", getPid());
  }
}

void cat(){
  char buffer[100] = {0};
  int exit= 0;
  while (!exit){
    scanf("%s", buffer);
    if (!strcmp(buffer, "/")){
      printf(buffer);
      printf("\n");
    } else {
      exit = 1;
    }
  }
}