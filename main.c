#include <stdio.h>
#include <locale.h>

#define MAX_CONTACTOS 100

typedef struct {
    char nome[50];
    char apelido[50];
    char tele[50];
    char email[50];
    char obs[50];
} Contacto;

Contacto agenda[MAX_CONTACTOS];
int numContactos = 0;

void NC(char input[200]){
            Contacto newContacto;

            char observacoes[50];
            int frase = sscanf(input, "NC %s %s %s %s %[^\n]", newContacto.nome, newContacto.apelido, newContacto.tele, newContacto.email, observacoes);
            if(frase < 1){
                    system("cls");
                    printf("\n> Formato inv�lido. Formato: NC Nome Apelido Telefone Email Observacoes <\n");
                    return;
            }

            int existeDup = 0;
            for(int i = 0; i < numContactos; i++){
                if(strcmp(agenda[i].nome, newContacto.nome) == 0){
                    existeDup = 1;
                    system("cls");
                    printf("\n> J� existe um contacto com o nome %s <\n", agenda[i].nome);
                    break;
                }
            }
            if (existeDup) return;

            strncpy(newContacto.obs, observacoes, sizeof(newContacto.obs) - 1);
            newContacto.obs[sizeof(newContacto.obs) - 1] = '\0';
            agenda[numContactos++] = newContacto;
            system("cls");
            printf("\n> Contacto registado com sucesso\n");
            printf("\n>> ENTER para voltar");
            getchar();
            system("cls");
}

void PC(char input[200]){
            system("cls");

            char nome[50];
            int frase = sscanf(input, "PC %s", nome);

            if(frase < 1 || nome[0] == '\0'){
                    system("cls");
                    printf("\n> Formato inv�lido. Formato: NC Nome <\n");
                    return;
            }

            printf("\n> Contacto a procurar: %s\n", nome);
            int encontrado = 0;

            for (int i = 0; i < numContactos; i++) {
                if (strcmp(agenda[i].nome, nome) == 0) {
                    printf("\nContacto encontrado: %s %s, %s, %s, %s\n", agenda[i].nome, agenda[i].apelido, agenda[i].tele, agenda[i].email, agenda[i].obs);
                    encontrado = 1;
                    break;
                }
            }
            if(encontrado==0) printf("\n> Contacto inexistente.\n");

}

void LC(){
     if (numContactos == 0) {
                system("cls");
                printf("\nAgenda sem contactos.\n");
            }else{
                system("cls");
                printf("\n> Contactos <\n");
                for(int i = 0; i < numContactos; i++){
                    printf("\n> [ID] %d | Nome e Apelido: %s %s, Telefone: %s, Email:%s, Obs:%s", i + 1, agenda[i].nome, agenda[i].apelido, agenda[i].tele, agenda[i].email, agenda[i].obs);
                }
        }
}

void AC(char input[200]){
        char nome[50];
        int frase = sscanf(input, "AC %s", nome);
        if(frase < 1 || nome[0] == '\0'){
                system("cls");
                printf("\n> Formato inv�lido. Formato: AC Nome <\n");
                return;
        }

        int encontrado = 0;

        for (int i = 0; i < numContactos; i++){
            if (strcmp(agenda[i].nome, nome) == 0){
                encontrado = 1;
                int opcao;

                do{
                   system("cls");
                    printf("\n> Contacto a atualizar : %s <", agenda[i].nome);
                    printf("\n\n> INFO ATUAL DO CONTACTO | Nome e Apelido: %s %s, Telefone: %s, Email:%s, Obs:%s", agenda[i].nome, agenda[i].apelido, agenda[i].tele, agenda[i].email, agenda[i].obs);
                    printf("\n\n[1] Atualizar Apelido\n[2] Atualizar Telefone\n[3] Atualizar Email\n[4] Atualizar Observa��es\n[5] Atualizar Sair\n");
                    printf("\nEscolha uma op��o: ");
                    scanf("%d", &opcao);
                    getchar();

                    switch (opcao) {
                        case 1:
                            system("cls");
                            printf("> Apelido atual: %s <", agenda[i].apelido);
                            printf("\nNovo apelido: ");
                            scanf("%49s", agenda[i].apelido);
                            break;

                        case 2:
                            system("cls");
                            printf("> Telefone atual: %s <", agenda[i].tele);
                            printf("\nNovo telefone: ");
                            scanf("%49s", agenda[i].tele);
                            break;

                        case 3:
                            system("cls");
                            printf("> Email atual: %s <", agenda[i].email);
                            printf("\nNovo email: ");
                            scanf("%49s", agenda[i].email);
                            break;

                        case 4:
                            system("cls");
                            printf("> Observa��es atuais: %s <", agenda[i].obs);
                            printf("\nNovas observa��es: ");
                            fgets(agenda[i].obs, sizeof(agenda[i].obs), stdin);
                            agenda[i].obs[strcspn(agenda[i].obs, "\n")] = '\0';
                            break;

                        case 5:
                            system("cls");
                            printf("\nContacto atualizado com sucesso.\n");
                            break;

                        default:
                            system("cls");
                            printf("\nOp��o inv�lida!\n");
                    }
                } while (opcao != 5);
                break;
            }
        }
}

void EC(char input[200]){
    char nome[50];
    int frase = sscanf(input, "EC %s", nome);
    if(frase < 1 || nome[0] == '\0'){
            system("cls");
            printf("\n> Formato inv�lido. Formato: EC Nome <\n");
            return;
    }

    int encontrado = 0;

        for (int i = 0; i < numContactos; i++) {
            if (strcmp(agenda[i].nome, nome) == 0) {
                encontrado = 1;
                printf("Contacto encontrado!\nTem a certeza que pretende eliminar? (s/n)\n>>");
                char escolha;
                scanf("%c", &escolha);
                getchar(); // LIMPAR O BUFFER
                if(escolha=='s'){
                    for (int j = i; j < numContactos - 1; j++) {
                        agenda[j] = agenda[j + 1];
                    }
                    numContactos--;
                    system("cls");
                    printf("\n> Contacto eliminado com sucesso <\n");
                    break;
                }else{
                    system("cls");
                    printf("\n> Cancelado! <\n");
                    break;
                } // FIM DO IF
            } // FIM DO IF
        } // FIM DO FOR

        if (!encontrado){
                system("cls");
                printf("\n> Contacto n�o encontrado <\n");
                return;
        }
}

int main() {

    setlocale(LC_ALL, "Portuguese");

    char input[200];
    int continuar = 1;

    while (continuar) {
        // Menu
        printf("\n");
        printf("\n ================================================================================================\n");
        printf(" ||                              Agenda de Contactos                                           ||\n");
        printf(" ================================================================================================\n");
        printf(" ||  NC    |  [Novo Contacto]      - Uso: NC <Nome> <Apelido> <Telefone> <Email> <Observa��es> ||\n");
        printf(" ================================================================================================\n");
        printf(" ||  PC    |  [Procurar Contacto]  - Uso: PC <Nome>                                            ||\n");
        printf(" ================================================================================================\n");
        printf(" ||  LC    |  [Listar Contactos]                                                               ||\n");
        printf(" ================================================================================================\n");
        printf(" ||  AC    |  [Atualizar Contacto] - Uso: AC <Nome>                                            ||\n");
        printf(" ================================================================================================\n");
        printf(" ||  EC    |  [Eliminar Contacto]  - Uso: EC <Nome>                                            ||\n");
        printf(" ================================================================================================\n");
        printf(" ||  XXX   |  [Sair]                                                                           ||\n");
        printf(" ================================================================================================\n");

        printf("\n > Comando:  ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if(strncmp(input, "NC", 2) == 0){
            if(numContactos >= MAX_CONTACTOS){
                printf("\n> Agenda cheia! <\n");
                continue;
            }
            NC(input);
        }else if (strncmp(input, "PC", 2) == 0){
            PC(input);
        }else if(strcmp(input, "LC") == 0){
            LC();
        }else if(strncmp(input, "AC", 2) == 0){
            AC(input);
        }else if(strncmp(input, "EC", 2) == 0){
            EC(input);
        }else if(strcmp(input, "XXX") == 0){
            system("cls");
            printf("\nA guardar a agenda...\nSayonara!\n");
            continuar = 0;
        }else{
            system("cls");
            printf("\n> Comando inv�lido! <\n");
        } // FIM DO IF

    } // FIM DO LOOP

    return 0;
}
