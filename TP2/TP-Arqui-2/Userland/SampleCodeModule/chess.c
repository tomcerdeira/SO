
#include <chess.h>
#include <stddef.h>

char firstTimePlaying = 1;
tablero_type tablero;
int isHorizontal = 1;
player player1;
player player2;

player *currentPlayer;

void initChess()
{
    if (firstTimePlaying)
    {

        //firstTimePlaying = 0;
        printf("Configurando el juego...\n");
        clearConsoleIn(0);
        tablero.up = 0;
        for (int i = 0; i < WIDTH; i++)
        {
            for (int j = 0; j < HEIGHT; j++)
            {
                tablero.matriz[j][i].pieceCode = EMPTY_CODE;
            }
        }

        ////CARGO EL TABLERO CON LAS PIEZAS

        //Pongo los PEONES
        for (int i = 0; i < WIDTH; i++)
        {
            piece peon_negro;
            peon_negro.color = BLACK_PIECE;
            peon_negro.firstMove = 1;
            peon_negro.pieceCode = PEON;
            peon_negro.posX = i;
            peon_negro.posY = 1;
            peon_negro.isActive = 1;
            tablero.matriz[peon_negro.posY][peon_negro.posX] = peon_negro;

            piece peon_blanco;
            peon_blanco.color = WHITE_PIECE;
            peon_blanco.firstMove = 1;
            peon_blanco.pieceCode = PEON;
            peon_blanco.posX = i;
            peon_blanco.posY = 6;
            peon_blanco.isActive = 1;
            tablero.matriz[peon_blanco.posY][peon_blanco.posX] = peon_blanco;
        }

        //Pongo las TORRES
        piece torre_negra;
        torre_negra.color = BLACK_PIECE;
        torre_negra.firstMove = 1;
        torre_negra.pieceCode = TORRE;
        torre_negra.posX = 0;
        torre_negra.posY = 0;
        torre_negra.isActive = 1;
        tablero.matriz[torre_negra.posY][torre_negra.posX] = torre_negra;
        torre_negra.posX = WIDTH - 1;
        tablero.matriz[torre_negra.posY][torre_negra.posX] = torre_negra;

        piece torre_blanca;
        torre_blanca.color = WHITE_PIECE;
        torre_blanca.firstMove = 1;
        torre_blanca.pieceCode = TORRE;
        torre_blanca.posX = 0;
        torre_blanca.posY = HEIGHT - 1;
        torre_blanca.isActive = 1;
        tablero.matriz[torre_blanca.posY][torre_blanca.posX] = torre_blanca;
        torre_blanca.posX = WIDTH - 1;
        tablero.matriz[torre_blanca.posY][torre_blanca.posX] = torre_blanca;

        //Pongo los CABALLOS
        piece caballo_negro;
        caballo_negro.color = BLACK_PIECE;
        caballo_negro.firstMove = 1;
        caballo_negro.pieceCode = CABALLO;
        caballo_negro.posX = 1;
        caballo_negro.posY = 0;
        caballo_negro.isActive = 1;
        tablero.matriz[caballo_negro.posY][caballo_negro.posX] = caballo_negro;
        caballo_negro.posX = WIDTH - 2;
        tablero.matriz[caballo_negro.posY][caballo_negro.posX] = caballo_negro;

        piece caballo_blanco;
        caballo_blanco.color = WHITE_PIECE;
        caballo_blanco.firstMove = 1;
        caballo_blanco.pieceCode = CABALLO;
        caballo_blanco.posX = 1;
        caballo_blanco.posY = HEIGHT - 1;
        caballo_blanco.isActive = 1;
        tablero.matriz[caballo_blanco.posY][caballo_blanco.posX] = caballo_blanco;
        caballo_blanco.posX = WIDTH - 2;
        tablero.matriz[caballo_blanco.posY][caballo_blanco.posX] = caballo_blanco;

        //Pongo los ALFILES
        piece alfil_negro;
        alfil_negro.color = BLACK_PIECE;
        alfil_negro.firstMove = 1;
        alfil_negro.pieceCode = ALFIL;
        alfil_negro.posX = 2;
        alfil_negro.posY = 0;
        alfil_negro.isActive = 1;
        tablero.matriz[alfil_negro.posY][alfil_negro.posX] = alfil_negro;
        alfil_negro.posX = WIDTH - 3;
        tablero.matriz[alfil_negro.posY][alfil_negro.posX] = alfil_negro;

        piece alfil_blanco;
        alfil_blanco.color = WHITE_PIECE;
        alfil_blanco.firstMove = 1;
        alfil_blanco.pieceCode = ALFIL;
        alfil_blanco.posX = 2;
        alfil_blanco.posY = HEIGHT - 1;
        alfil_blanco.isActive = 1;
        tablero.matriz[alfil_blanco.posY][alfil_blanco.posX] = alfil_blanco;
        alfil_blanco.posX = WIDTH - 3;
        int pos[3];
        pos[0] = 250;
        pos[1] = 10;
        int heightWidth[2];
        heightWidth[0] = WIDTH;
        heightWidth[1] = HEIGHT;

      
        tablero.matriz[alfil_blanco.posY][alfil_blanco.posX] = alfil_blanco;

        //Pongo las REINAS
        piece reina_negro;
        reina_negro.color = BLACK_PIECE;
        reina_negro.firstMove = 1;
        reina_negro.pieceCode = REINA;
        reina_negro.posX = 3;
        reina_negro.posY = 0;
        reina_negro.isActive = 1;
        tablero.matriz[reina_negro.posY][reina_negro.posX] = reina_negro;

        piece reina_blanco;
        reina_blanco.color = WHITE_PIECE;
        reina_blanco.firstMove = 1;
        reina_blanco.pieceCode = REINA;
        reina_blanco.posX = 3;
        reina_blanco.posY = HEIGHT - 1;
        reina_blanco.isActive = 1;
        tablero.matriz[reina_blanco.posY][reina_blanco.posX] = reina_blanco;

        //Pongo los REYES
        piece rey_negro;
        rey_negro.color = BLACK_PIECE;
        rey_negro.firstMove = 1;
        rey_negro.pieceCode = REY;
        rey_negro.posX = 4;
        rey_negro.posY = 0;
        rey_negro.isActive = 1;
        tablero.matriz[rey_negro.posY][rey_negro.posX] = rey_negro;

        piece rey_blanco;
        rey_blanco.color = WHITE_PIECE;
        rey_blanco.firstMove = 1;
        rey_blanco.pieceCode = REY;
        rey_blanco.posX = 4;
        rey_blanco.posY = HEIGHT - 1;
        rey_blanco.isActive = 1;
        tablero.matriz[rey_blanco.posY][rey_blanco.posX] = rey_blanco;

        printf("Introduzca un nombre para ");
        setFontColor(PLAYER1_COLOR);
        printf("PLAYER1");
        setFontColor(DEFAULT_FONT_COLOR);
        printf(": ");
        scanf("%s", &player1.name);
        printf("\n");
        setFontColor(PLAYER1_COLOR);
        printf("%s ", player1.name);
        setFontColor(DEFAULT_FONT_COLOR);
        printf("desea ser BLANCAS(1) o NEGRAS(0): ", player1.name);
        int d = -1;
        while (d == -1)
        {
            scanf("%d", &player1.color);
            printf("\n");
            if (player1.color == BLACK_PIECE || player1.color == WHITE_PIECE)
            {
                d = 1;
            }
            else
            {
                setFontColor(PLAYER1_COLOR);
                printf("%s ", player1.name);
                setFontColor(DEFAULT_FONT_COLOR);
                printf("desea ser BLANCAS(1) o NEGRAS(0): ", player1.name);
            }
        }
        
        printf("Introduzca un nombre para ");
        setFontColor(PLAYER2_COLOR);
        printf("PLAYER2");
        setFontColor(DEFAULT_FONT_COLOR);
        printf(": ");
        scanf("%s", &player2.name);
        printf("\n");
        setFontColor(PLAYER2_COLOR);
        printf("%s ", player2.name);
        setFontColor(DEFAULT_FONT_COLOR);
        printf("es %s", (player1.color == 0) ? "BLANCAS(1)\n" : "NEGRAS(0)\n");
        printf("\n");

        player1.play_number = 0;
        player2.play_number = 0;

        if (player1.color == BLACK_PIECE)
        {
            player2.color = WHITE_PIECE;
            currentPlayer = &player2;
        }
        else
        {
            player2.color = BLACK_PIECE;
            currentPlayer = &player1;
        }
    }
    else
    {
        printf("Bienvenidos nuevamente...\n");
        clearConsoleIn(5);
    }
    chessManager();
}

char validPeonMovement(piece *piecePointer, int toX, int toY)
{
    piece piece = *piecePointer;
    int distY = piece.posY - toY;
    int distX = piece.posX - toX;

    if (piece.color == BLACK_PIECE)
    {
        if (distY > 0)
        {
            return 0;
        }
        distY *= -1; // para trabajar con el modulo mas abajo
    }
    else
    {
        if (distY < 0)
        {
            return 0;
        }
    }

 
    if (piece.firstMove == 1)
    {
        

        if (distX == 0 && distY != 0 && distY <= 2 && positionIsFree(toX, toY))
        { // dice si esta libre
            
            return 1;
        }
    }
    else
    {
        if (distX == 0 && distY == 1 && positionIsFree(toX, toY))
        {
            return 1;
        }
    }


    if ((distX == 1 || distX == -1) && distY == 1)
    {
  
        return validPosition(toX, toY, piece.color); // si puedo moverme ahi ( en estre a comer)
    }

    return 0;
}

char validCaballoMovement(piece *piecePointer, int toX, int toY)
{
    piece piece = *piecePointer;
    int distY = getDistance(toY, piece.posY); //distancia con respecto a Y en modulo
    int distX = getDistance(toX, piece.posX);

    if (validPosition(toX, toY, piece.color)) // si puedo moverme ahi ( en estre a comer)
    {
        if (distY == 2 && distX == 1) //como es el modulo toma los casos en los que se mueve para delante o para atras
        {
            return 1;
        }
        else if (distY == 1 && distX == 2)
        {
            return 1;
        }
    }
    return 0;
}

char validAlfilMovement(piece *piecePointer, int toX, int toY)
{
    piece piece = *piecePointer;
    int distY = getDistance(toY, piece.posY); //distancia con respecto a Y en modulo
    int distX = getDistance(toX, piece.posX);

    if (distX != distY || !validPosition(toX, toY, piece.color))
    {
        return 0;
    }

    if (toX > piece.posX && toY < piece.posY) // 0
    {
        for (int i = piece.posX + 1; i < toX; i++) //+1 para arrancar en la proxima posicion
        {
            for (int j = piece.posY - 1; j > toY; j--) //-1 para lo mismo (ya que es en digonal)
            {
                if (!positionIsFree(i, j))
                {
                    return 0;
                }
            }
        }
    }
    else if (toX > piece.posX && toY > piece.posY) // 1
    {
        for (int i = piece.posX + 1; i < toX; i++)
        {
            for (int j = piece.posY + 1; j < toY; j++)
            {
                if (!positionIsFree(i, j))
                {
                    return 0;
                }
            }
        }
    }
    else if (toX < piece.posX && toY < piece.posY) // 2
    {
        for (int i = piece.posX + 1; i < toX; i++)
        {
            for (int j = piece.posY + 1; j < toY; j++)
            {
                if (!positionIsFree(i, j))
                {
                    return 0;
                }
            }
        }
    }
    else if (toX < piece.posX && toY > piece.posY) // 3
    {
        for (int i = piece.posX - 1; i > toX; i--)
        {
            for (int j = piece.posY + 1; j < toY; j++)
            {
                if (!positionIsFree(i, j))
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}

char validTorreMovement(piece *piecePointer, int toX, int toY)
{
    piece piece = *piecePointer;
    int distY = getDistance(toY, piece.posY); //distancia con respecto a Y en modulo
    int distX = getDistance(toX, piece.posX);

    // Si no se mueve en linea recta o va a un lugar donde hay uno suyo  EEROR
    if ((distX != 0 && distY != 0) || !validPosition(toX, toY, piece.color))
    {
        return 0;
    }

    if (distX == 0)
    {
        // Linea recta vertical
        if (toY > piece.posY)
        {
            for (int i = piece.posY + 1; i < toY; i++)
            {
                if (!positionIsFree(toX, i))
                {
                    return 0;
                }
            }
        }
        else
        {
            for (int i = piece.posY - 1; i > toY; i--)
            {
                if (!positionIsFree(toX, i))
                {
                    return 0;
                }
            }
        }
    }
    else
    {
        // Linea recta horizontal
        if (toX > piece.posX)
        {
            for (int i = piece.posX + 1; i < toX; i++)
            {
                if (!positionIsFree(i, toY))
                {
                    return 0;
                }
            }
        }
        else
        {
            for (int i = piece.posX - 1; i > toX; i--)
            {
                if (!positionIsFree(i, toY))
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}

char validReinaMovement(piece *piecePointer, int toX, int toY)
{
    return validAlfilMovement(piecePointer, toX, toY) || validTorreMovement(piecePointer, toX, toY);
}

char validReyMovement(piece *piecePointer, int toX, int toY)
{
    piece piece = *piecePointer;
    int distY = getDistance(toY, piece.posY); //distancia con respecto a Y en modulo
    int distX = getDistance(toX, piece.posX);

    if (distY == 0 && distX == 2)
    {
        return validEnroque(*piecePointer, toX, toY);
    }

    if (distX != 1 && distY != 1 && !validPosition(toX, toY, piece.color))
    {
        return 0;
    }
    return 1;
}

int validPosition(int toX, int toY, int pieceColor)
{
    if (!positionIsFree(toX, toY))
    {
        
        if (tablero.matriz[toY][toX].color == pieceColor)
        {
            return 0;
        }
    }
    return 1;
}

int positionIsFree(int toX, int toY)
{
    piece c = tablero.matriz[toY][toX];
    printf("EN EL LUGAR %d ", tablero.matriz[toY][toX].pieceCode);
    if (c.pieceCode != EMPTY_CODE)
    {

        return 0;
    }
    return 1;
}

int validEnroque(piece pieceT, int toX, int toY)
{
    int distY = getDistance(toY, pieceT.posY);
    int distX = getDistance(toX, pieceT.posX);

    if (distY != 0 || distX != 2 || !pieceT.firstMove || pieceT.pieceCode != REY)
    {
        return 0;
    }

    if (toX > pieceT.posX)
    {
        if (tablero.matriz[pieceT.posY][WIDTH - 1].pieceCode != TORRE || !tablero.matriz[pieceT.posY][WIDTH - 1].firstMove)
        {
            return 0;
        }
        piece *toMove = &tablero.matriz[pieceT.posY][WIDTH - 1];
        toMove->firstMove = 0;
        toMove->posX = WIDTH - 3;
        toMove->posY = toY;
        tablero.matriz[toY][WIDTH - 3] = tablero.matriz[pieceT.posY][WIDTH - 1];
        tablero.matriz[pieceT.posY][WIDTH - 1].pieceCode = EMPTY_CODE;
    }
    else
    {
        if (tablero.matriz[pieceT.posY][0].pieceCode != TORRE || !tablero.matriz[pieceT.posY][0].firstMove)
        {
            return 0;
        }
        piece *toMove = &tablero.matriz[pieceT.posY][0];
        toMove->firstMove = 0;
        toMove->posX = 2;
        toMove->posY = toY;
        tablero.matriz[toY][2] = tablero.matriz[pieceT.posY][0];
        tablero.matriz[pieceT.posY][0].pieceCode = EMPTY_CODE;
    }
    return 1;
}

int isPossible(piece *piece, int coord_x, int coord_y)
{

    if (piece->pieceCode == PEON)
    {
        int value = validPeonMovement(piece, coord_x, coord_y);
        return value;
    }
    else if (piece->pieceCode == TORRE)
    {
        int value = validTorreMovement(piece, coord_x, coord_y);
        return value;
    }
    else if (piece->pieceCode == ALFIL)
    {
        int value = validAlfilMovement(piece, coord_x, coord_y);
        return value;
    }
    else if (piece->pieceCode == CABALLO)
    {
        int value = validCaballoMovement(piece, coord_x, coord_y);
        return value;
    }
    else if (piece->pieceCode == REY)
    {
        int value = validReyMovement(piece, coord_x, coord_y);
        return value;
    }
    else if (piece->pieceCode == REINA)
    {
        int value = validReinaMovement(piece, coord_x, coord_y);
        return value;
    }
    else
    {
        return 0;
    }
}
long startMillis = 0;
int changeTurn()
{
    long currentMillis = getMillis();
    int time = currentMillis - startMillis;
    if (time >= ALLOWED_SECONDS)
        {
            return 0;
        }
    
    if (strcmp(currentPlayer->name, player1.name))
    {
        
        
        currentPlayer = &player2;
        setCronometro(1);
    }
    else
    {
        setCronometro(1);
        currentPlayer = &player1;
    }

    return 1;
}

void printHistoriales()
{
    int x = PLAYER1_PRINT_X;
    int y = PLAYER1_PRINT_Y;
    setCursorUser(x, y);
    writeScreen(player1.name, 0xFFFFFF, 0x000000);
    for (int i = 0; i < player1.play_number; i++)
    {
        char buffer[9];
        buffer[0] = player1.historial[i].from[0];
        buffer[1] = player1.historial[i].from[2];

        buffer[2] = ' ';
        buffer[3] = 't';
        buffer[4] = 'o';
        buffer[5] = ' ';
        buffer[6] = player1.historial[i].to[0];
        buffer[7] = player1.historial[i].to[2];
        buffer[8] = 0;
        int x = PLAYER1_PRINT_X;
        int y = PLAYER1_PRINT_Y + (i + 1) * CHAR_HEIGHT;
        setCursorUser(x, y);

        writeScreen(buffer, 0xFFFFFF, 0x000000);
    }
    disableCursor();
    x = PLAYER2_PRINT_X;
    y = PLAYER2_PRINT_Y;
    setCursorUser(x, y);
    writeScreen(player2.name, 0xFFFFFF, 0x000000);

    for (int i = 0; i < player2.play_number; i++)
    {
        char buffer[9];
        buffer[0] = player2.historial[i].from[0];
        buffer[1] = player2.historial[i].from[2];

        buffer[2] = ' ';
        buffer[3] = 't';
        buffer[4] = 'o';
        buffer[5] = ' ';
        buffer[6] = player2.historial[i].to[0];
        buffer[7] = player2.historial[i].to[2];
        buffer[8] = 0;
        int x = PLAYER2_PRINT_X;
        int y = PLAYER2_PRINT_Y + (i + 1) * CHAR_HEIGHT;
        setCursorUser(x, y + i * HEIGHT);

        writeScreen(buffer, 0xFFFFFF, 0x000000);
        disableCursor();
    }
}

void reDrawTable()
{

    printHistoriales();
    if (isHorizontal)
    {
        for (int i = 0; i < WIDTH; i++)
        {
            for (int j = 0; j < HEIGHT; j++)
            {

                uint64_t pos[3];
                pos[0] = 400 + i * WIDTH * 4;
                pos[1] = 250 + j * HEIGHT * 4;
                uint64_t heightWidth[3];
                heightWidth[0] = WIDTH * 4;
                heightWidth[1] = HEIGHT * 4;

                if ((i + j) % 2 == 0)
                {
                    printRectangle(pos, 0x000000, heightWidth);
                }
                else
                {
                    printRectangle(pos, 0xFFFFFF, heightWidth);
                }

                int pieceCode = tablero.matriz[j][i].pieceCode;
                char name[6];
                switch (pieceCode)
                {
                case (PEON):
                {
                    name[0] = 'p';
                    break;
                }
                case (TORRE):
                {
                    name[0] = 'T';
                    break;
                }
                case (REINA):
                {
                    name[0] = 'Y';
                    break;
                }
                case (CABALLO):
                {
                    name[0] = 'C';
                    break;
                }
                case (ALFIL):
                {
                    name[0] = 'A';
                    break;
                }
                case (REY):
                {
                    name[0] = 'X';
                    break;
                }
                default:
                    name[0] = 0;
                    break;
                }

                if (tablero.matriz[j][i].color == player1.color)
                {
                    setCursorUser(400 + i * WIDTH * 4, 250 + j * HEIGHT * 4);
                    setFontColor(0x000000); // hacer la cte
                    setBackGroundColor(PLAYER1_COLOR);
                    printf("%s", name);
                    setBackGroundColor(DEFAULT_BACKGROUND_COLOR);
                    setFontColor(DEFAULT_FONT_COLOR);
                    disableCursor();
                }
                else if (tablero.matriz[j][i].color == player2.color)
                {
                    setCursorUser(400 + i * WIDTH * 4, 250 + j * HEIGHT * 4);
                    setFontColor(0xFFFFFF); // hacer la cte
                    setBackGroundColor(PLAYER2_COLOR);
                    printf("%s", name);
                    setBackGroundColor(DEFAULT_BACKGROUND_COLOR);
                    setFontColor(DEFAULT_FONT_COLOR);
                    disableCursor();
                }

                if (j == 0)
                {
                    setCursorUser(400 + i * WIDTH * 4, 250 - WIDTH * 4);
                    char leter = 'A' + i;
                    printf("  %c ", leter);

                    disableCursor();
                }
                if (i == 0)
                {
                    setCursorUser(400 - WIDTH * 4, 250 + j * HEIGHT * 4);
                    printf("%d", (j + 1));
                    disableCursor();
                }
            }
        }
    }
    else
    {
         for(int i=0;i<WIDTH;i++){
        for(int j=0;j<HEIGHT;j++){

            uint64_t pos[3];
            pos[0]=400+i*WIDTH*4;
            pos[1]=250+j*HEIGHT*4;
            uint64_t heightWidth[3];
            heightWidth[0] = WIDTH*4;
            heightWidth[1] = HEIGHT*4;

           

            int pieceCode = tablero.matriz[j][i].pieceCode;
            char name[6];
            switch (pieceCode)
            {
            case(PEON):
            {
                name[0]='p';
                break;
            }
            case(TORRE):
            {
                name[0]='T';
                break;
            }
            case(REINA):
            {
                name[0]='Y';
                break;
            }
            case(CABALLO):
            {
                name[0]= 'C';
                break;
            }
            case(ALFIL):
            {
                name[0]='A';
                break;
            }
            case(REY):
            {
                name[0]='X';
                break;
            }
            default:
                name[0]=0;
                break;
            }
               if((i+j) %2 !=0){
                printRectangle(pos,0xFFFFFF,heightWidth);
            }
          
            if(tablero.matriz[j][i].color == player1.color){
            setCursorUser(400+(7-j)*WIDTH*4,250+(i)*HEIGHT*4);  ////
            setFontColor(0x000000); // hacer la cte
            setBackGroundColor(PLAYER1_COLOR);
            printf("%s",name);
            setBackGroundColor(DEFAULT_BACKGROUND_COLOR);
            setFontColor(DEFAULT_FONT_COLOR);
            disableCursor();
            }else if(tablero.matriz[j][i].color == player2.color){
            setCursorUser(400+(7-j)*WIDTH*4,250+(i)*HEIGHT*4); //
            setFontColor(0xFFFFFF); // hacer la cte
            setBackGroundColor(PLAYER2_COLOR);
            printf("%s",name);
            setBackGroundColor(DEFAULT_BACKGROUND_COLOR);
            setFontColor(DEFAULT_FONT_COLOR);
            disableCursor();
            }
           
             
            if(j==0){
                setCursorUser(400+i*WIDTH*4,250-WIDTH*4);
                 printf("%d",(i+1));
                 disableCursor();
            }
            if(i==0){
                 setCursorUser(400-WIDTH*4,250+j*HEIGHT*4);
                
                 
                 char leter = 'A'+j;
                printf("  %c ",leter);
                disableCursor();
            }
        }

         }
    }
}

void chessManager()
{
    // Formato de entrada jugadar   Xinicial-Yincial  xFinal-yFinal
    int exit = 0;
    char bufferIncial[10] = {0};
    char bufferFinal[10] = {0};
     startMillis = getMillis();
    setCronometro(1); //empiezo el cronometro
    while (!exit)
    {   
       
        clearConsoleIn(0);
        reDrawTable();
        printf("Turno de ");
        if (strcmp(currentPlayer->name, player1.name))
        {
            setFontColor(PLAYER1_COLOR);
        }
        else
        {
            setFontColor(PLAYER2_COLOR);
        }
        printf("%s\n", currentPlayer->name);
        setFontColor(DEFAULT_FONT_COLOR);
        printf("Recuerde: puede ingresar \"exit\" para salir, \"rotate\" para rotar el tablero o \"clear\" para limpiar la pantalla\n");
        setFontColor(0xFF0000);
        printf("FORMATO DE JUGADA: LETRA-NUMERO\n");
        printf("e.j. a-1 o A-1\n");
        printf("\n");
        setFontColor(DEFAULT_FONT_COLOR);
        printf("Pieza a mover: ");
        scanf("%s", bufferIncial);
        printf("\n");
        printf("Al casillero: ");
        scanf("%s", bufferFinal);
        printf("\n");
        //reDrawTable();

        if (strcmp(bufferIncial, "exit") != 0 || strcmp(bufferIncial, "EXIT") != 0 || strcmp(bufferFinal, "exit") != 0 || strcmp(bufferFinal, "EXIT") != 0)
        {
            printf("Estas seguro que queres salir?\n");
            printf("Ingrese 1 para confirmar, 0 para cancelar: ");
            int c;
            scanf("%d", &c);
            if (c == 1)
            {
                exit = 1;
                printf("\n");
                clearConsoleIn(3);
            }
        }
        else if (strcmp(bufferIncial, "rotate") != 0 || strcmp(bufferIncial, "ROTATE") != 0 || strcmp(bufferFinal, "rotate") != 0 || strcmp(bufferFinal, "ROTATE") != 0)
        {
            clearConsoleIn(0);
            if(isHorizontal == 1){
                isHorizontal =0;
            }else
            {
                isHorizontal =1;
            }
            
            
            // reDrawTable();
        }
        else if (strcmp(bufferIncial, "clear") != 0 || strcmp(bufferIncial, "CLEAR") != 0 || strcmp(bufferFinal, "clear") != 0 || strcmp(bufferFinal, "CLEAR") != 0)
        {
            clearConsoleIn(0);
            reDrawTable();
        }
        else if (checkCorrectMovement(bufferIncial, bufferFinal) != 0)
        {
            int flag = makeMove(bufferIncial, bufferFinal);
            if (flag == 1) //pudo hacer el movimiento bien
            {
                clearConsoleIn(0);
                int cont = changeTurn();
                if (cont == 0)
                {
                    printf("%s perdio la partida por tardar mas del tiempo determinado. \n",currentPlayer->name);
                    exit = 1;
                    
                }
                //reDrawTable();
            }
            else if (flag == 0)
            {
                setFontColor(0xFF0000);
                printf("Ese movimiento NO es posible.\n");
                setFontColor(DEFAULT_FONT_COLOR);
            }
            else if (flag == 2)
            {
                clearConsoleIn(0);
                reDrawTable();
                setFontColor(WINNER_COLOR);
                printf("%s ha ganado!", &currentPlayer->name);
                printf("Muchas gracias por jugar, hasta la proxima.");
                setFontColor(DEFAULT_FONT_COLOR);
                firstTimePlaying = 1;
                clearConsoleIn(5);
                return;
            }
        }
        else
        {
            setFontColor(0xFF0000);
            printf(" Operacion invalida. ");
            setFontColor(DEFAULT_FONT_COLOR);
        }
    }
    printf("Esperamos volver a verte. Presiona 1 para guardar la partida, 0 para borrarla \n");
    int c;
    scanf("%d", &c);

    if (c == 1)
    {
        firstTimePlaying = 0;
    }
    else
    {
        firstTimePlaying = 1;
    }
    setCronometro(0);
    return;
}

int checkCorrectMovement(char *bufferInicial, char *bufferFinal)
{
    if (isLetterChess(bufferInicial[0]) && isNumberChess(bufferInicial[2]) && isLetterChess(bufferFinal[0]) && isNumberChess(bufferFinal[2]))
    {
        return 1;
    }
    return 0;
}

int isLetterChess(char c)
{
    if (c >= 'a' && c <= 'h')
    {
        return 1;
    }
    if (c >= 'A' && c <= 'H')
    {
        return 1;
    }
 
    return 0;
}

int isNumberChess(char c)
{
    if (c >= '1' && c <= '8')
    {
        return 1;
    }


    return 0;
}

// Formato de entrada jugadar   Xinicial-Yincial  xFinal-yFinal
int makeMove(char *bufferInicial, char *bufferFinal)
{
    int cordXInicial = 0;
    int cordYInicial = 0;

    int cordXFinal = 0;
    int cordYFinal = 0;

    if (bufferInicial[0] >= 'A' && bufferInicial[0] <= 'H')
    {
        cordXInicial = bufferInicial[0] - 'A';
    }
    else
    {
        cordXInicial = bufferInicial[0] - 'a';
    }

    cordYInicial = bufferInicial[2] - '0' - 1; // -1 es por que se imprime hasta el 8 pero en realidad hay hasta el 7

    if (bufferFinal[0] >= 'A' && bufferFinal[0] <= 'H')
    {
        cordXFinal = bufferFinal[0] - 'A';
    }
    else
    {
        cordXFinal = bufferFinal[0] - 'a';
    }

    cordYFinal = bufferFinal[2] - '0' - 1;

    piece *toMove = &tablero.matriz[cordYInicial][cordXInicial];

    if (toMove->pieceCode == EMPTY_CODE)
    {
        return 0;
    }

    if (!isPossible(toMove, cordXFinal, cordYFinal))
    {
        return 0;
    }

    if (tablero.matriz[cordYFinal][cordXFinal].pieceCode == REY)
    {
        return 2;
    }

    play thisPlay; 
    strcpy(thisPlay.from, bufferInicial);
    strcpy(thisPlay.to, bufferFinal);
    thisPlay.pieceC = *toMove;
    currentPlayer->historial[currentPlayer->play_number++] = thisPlay;
    toMove->firstMove = 0;
    toMove->posX = cordXFinal;
    toMove->posY = cordYFinal;
    tablero.matriz[cordYFinal][cordXFinal] = tablero.matriz[cordYInicial][cordXInicial];
    tablero.matriz[cordYInicial][cordXInicial].pieceCode = EMPTY_CODE;

    return 1;
}