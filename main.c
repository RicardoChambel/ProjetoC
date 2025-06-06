#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTACTOS 100

typedef struct {
    char nome[50];
    char apelido[50];
    char tele[50];
    char email[50];
    char obs[50];
} Contacto;

Contacto *agenda = NULL;
int numContactos = 0;

void RC(char input[200]){
    Contacto newContacto;

    char observacoes[50] = "";
    int frase = sscanf(input, "RC %49s %49s %49s %49s %[^\n]", newContacto.nome, newContacto.apelido, newContacto.tele, newContacto.email, observacoes);

    if (frase < 4) {
        system("cls");
        printf("\n> Formato inválido. Formato: RC Nome Apelido Telefone Email [Observacoes]\n");
        return;
    }

    int existeDup = 0;
    for (int i = 0; i < numContactos; i++) {
        if (strcmp(agenda[i].nome, newContacto.nome) == 0){
            existeDup = 1;
            system("cls");
            printf("\n> Contacto existente com o nome %s (Posição na Agenda: %d)\n", agenda[i].nome, i + 1);
            break;
        }
    }

    if (existeDup) return;

    strncpy(newContacto.obs, observacoes, sizeof(newContacto.obs) - 1);
    newContacto.obs[sizeof(newContacto.obs) - 1] = '\0';

    agenda = realloc(agenda, (numContactos + 1) * sizeof(Contacto));
    if (agenda == NULL) {
        printf("\nErro de alocação de memória!\n");
        exit(1);
    }

    if(numContactos < MAX_CONTACTOS){
        agenda[numContactos++] = newContacto;
        system("cls");
        printf("\n> Contacto registado com sucesso\n");
        printf("\n>> ENTER para voltar");
        getchar();
        system("cls");
    }else{
        system("cls");
        printf("\n> Agenda de contactos cheia!\n");
        printf("\n>> ENTER para voltar");
        getchar();
        system("cls");
    }

}

void PC(char input[200]){
    system("cls");

    char apelido[50];
    int frase = sscanf(input, "PC %s", apelido);

    if (frase < 1 || apelido[0] == '\0') {
        system("cls");
        printf("\n> Formato inválido. Formato: PC Apelido\n");
        return;
    }

    printf("\n> Contacto a procurar: %s\n", apelido);
    int encontrado = 0;

    for (int i = 0; i < numContactos; i++) {
        if (strcmp(agenda[i].apelido, apelido) == 0) {
            printf("\nContacto encontrado: %s %s, %s, %s, %s\n", agenda[i].nome, agenda[i].apelido, agenda[i].tele, agenda[i].email, agenda[i].obs);
            encontrado = 1;
            break;
        }
    }

    if (encontrado == 0) printf("\n> Contacto inexistente.\n");
}

void LC(){
    if (numContactos == 0) {
        system("cls");
        printf("\nAgenda sem contactos.\n");
    } else {
        system("cls");
        printf("\n> Contactos <\n");
        for (int i = 0; i < numContactos; i++) {
            printf("\n> [ID] %d | Nome e Apelido: %s %s, Telefone: %s, Email:%s, Obs:%s", i + 1, agenda[i].nome, agenda[i].apelido, agenda[i].tele, agenda[i].email, agenda[i].obs);
        }
    }
}

void AC(char input[200]){
    char nome[50];
    int frase = sscanf(input, "AC %s", nome);
    if (frase < 1 || nome[0] == '\0') {
        system("cls");
        printf("\n> Formato inválido. Formato: AC Nome\n");
        return;
    }

    int encontrado = 0;

    for (int i = 0; i < numContactos; i++) {
        if (strcmp(agenda[i].nome, nome) == 0) {
            encontrado = 1;
            int opcao;

            do {
                system("cls");
                printf("\n> Contacto a atualizar : %s <", agenda[i].nome);
                printf("\n\n> INFO ATUAL DO CONTACTO | Nome e Apelido: %s %s, Telefone: %s, Email:%s, Obs:%s", agenda[i].nome, agenda[i].apelido, agenda[i].tele, agenda[i].email, agenda[i].obs);
                printf("\n\n[1] Atualizar Apelido\n[2] Atualizar Telefone\n[3] Atualizar Email\n[4] Atualizar Observações\n[5] Sair\n");
                printf("\nEscolha uma opção: ");
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
                        printf("> Observações atuais: %s <", agenda[i].obs);
                        printf("\nNovas observações: ");
                        fgets(agenda[i].obs, sizeof(agenda[i].obs), stdin);
                        agenda[i].obs[strcspn(agenda[i].obs, "\n")] = '\0';
                        break;

                    case 5:
                        system("cls");
                        printf("\nContacto atualizado com sucesso.\n");
                        break;

                    default:
                        system("cls");
                        printf("\nOpção inválida!\n");
                }
            } while (opcao != 5);
            break;
        }
    }
}

void EC(char input[200]){
    char nome[50];
    int frase = sscanf(input, "EC %s", nome);
    if (frase < 1 || nome[0] == '\0') {
        system("cls");
        printf("\n> Formato inválido. Formato: EC Nome\n");
        return;
    }

    int encontrado = 0;

    for (int i = 0; i < numContactos; i++) {
        if (strcmp(agenda[i].nome, nome) == 0) {
            encontrado = 1;
            printf("Contacto encontrado!\nTem a certeza que pretende eliminar? (s/n)\n>>");
            char escolha;
            scanf("%c", &escolha);
            getchar();
            if (escolha == 's') {
                for (int j = i; j < numContactos - 1; j++) {
                    agenda[j] = agenda[j + 1];
                }
                numContactos--;
                system("cls");
                printf("\n> Contacto eliminado com sucesso <\n");
                break;
            } else {
                system("cls");
                printf("\n> Cancelado! <\n");
                break;
            }
        }
    }

    if (!encontrado) {
        system("cls");
        printf("\n> Contacto não encontrado <\n");
        return;
    }
}

void EXPC() {
    char *home = getenv("USERPROFILE");
    if (!home) {
        printf("\nErro ao obter o folder do user!\n");
        return;
    }

    char path[260];
    sprintf(path, "%s\\Desktop\\Contactos.txt", home);

    FILE *ficheiro = fopen(path, "w");
    if (!ficheiro) {
        printf("\nErro ao criar o ficheiro!\n");
        return;
    }

    for (int i = 0; i < numContactos; i++) {
        fprintf(ficheiro, "%s;%s;%s;%s;%s\n",
                agenda[i].nome,
                agenda[i].apelido,
                agenda[i].tele,
                agenda[i].email,
                agenda[i].obs);
    }

    fclose(ficheiro);
    printf("\n> Exportados %d contactos para: %s\n", numContactos, path);
}

void IMPC() {
    char *home = getenv("USERPROFILE");
    if (!home) {
        printf("\nErro ao obter o diretório do utilizador.\n");
        return;
    }

    char path[260];
    sprintf(path, "%s\\Desktop\\Contactos.txt", home);

    FILE *ficheiro = fopen(path, "r");
    if (!ficheiro) {
        printf("\nErro ao abrir o ficheiro!\n");
        return;
    }

    if (agenda != NULL) {
        free(agenda);
    }

    agenda = malloc(MAX_CONTACTOS * sizeof(Contacto));
    if (agenda == NULL) {
        printf("\nErro ao fazer malloc memória!\n");
        fclose(ficheiro);
        return;
    }

    char linha[300];

    while (numContactos < MAX_CONTACTOS && fgets(linha, sizeof(linha), ficheiro)) {
        linha[strcspn(linha, "\n")] = '\0';

        char *campo = strtok(linha, ";");
        int campoIndex = 0;

        strcpy(agenda[numContactos].nome, "");
        strcpy(agenda[numContactos].apelido, "");
        strcpy(agenda[numContactos].tele, "");
        strcpy(agenda[numContactos].email, "");
        strcpy(agenda[numContactos].obs, "");

        while (campo != NULL && campoIndex < 5) {
            switch (campoIndex) {
                case 0: strncpy(agenda[numContactos].nome, campo, 49); break;
                case 1: strncpy(agenda[numContactos].apelido, campo, 49); break;
                case 2: strncpy(agenda[numContactos].tele, campo, 49); break;
                case 3: strncpy(agenda[numContactos].email, campo, 49); break;
                case 4: strncpy(agenda[numContactos].obs, campo, 49); break;
            }
            campo = strtok(NULL, ";");
            campoIndex++;
        }

        if (campoIndex >= 2) {
            numContactos++;
        } else {
            printf("\nLinha ignorada (dados insuficientes)");
        }
    }

    fclose(ficheiro);
    printf("\n> Importados %d contactos de: %s\n", numContactos, path);
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    char input[200];
    int continuar = 1;

    while (continuar) {
        printf("\n");
        printf("\n ================================================================================================\n");
        printf(" ||                              Agenda de Contactos                                           ||\n");
        printf(" ================================================================================================\n");
        printf(" ||  RC    |  [Novo Contacto]      - Uso: RC <Nome> <Apelido> <Telefone> <Email> <Observações>\n");
        printf(" ================================================================================================\n");
        printf(" ||  PC    |  [Procurar Contacto]  - Uso: PC <Apelido>\n");
        printf(" ================================================================================================\n");
        printf(" ||  LC    |  [Listar Contactos]\n");
        printf(" ================================================================================================\n");
        printf(" ||  AC    |  [Atualizar Contacto] - Uso: AC <Nome>\n");
        printf(" ================================================================================================\n");
        printf(" ||  EC    |  [Eliminar Contacto]  - Uso: EC <Nome>\n");
        printf(" ================================================================================================\n");
        printf(" ||  EXPC  |  [Exportar contactos para ficheiro .txt]\n");
        printf(" ================================================================================================\n");
        printf(" ||  IMPC  |  [Importar contactos para ficheiro .txt]\n");
        printf(" ================================================================================================\n");
        printf(" ||  XXX   |  [Sair]\n");
        printf(" ================================================================================================\n");

        printf("\n > Comando:  ");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if (strncmp(input, "RC", 2) == 0) {
            RC(input);
        } else if (strncmp(input, "PC", 2) == 0) {
            PC(input);
        } else if (strcmp(input, "LC") == 0) {
            LC();
        } else if (strncmp(input, "AC", 2) == 0) {
            AC(input);
        } else if (strncmp(input, "EC", 2) == 0) {
            EC(input);
        } else if (strcmp(input, "XXX") == 0) {
            system("cls");
            printf("\nA guardar a agenda...\nSayonara!\n");
            continuar = 0;
        } else if (strcmp(input, "EXPC") == 0) {
            EXPC();
        } else if (strcmp(input, "IMPC") == 0) {
            IMPC();
        } else {
            system("cls");
            printf("\n> Comando inválido! <\n");
        }
    }

    free(agenda);
    return 0;
}
