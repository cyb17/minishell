#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

// Fonction de gestion du signal SIGINT (Ctrl-C)
void handle_sigint(int signum) {
    if (signum == SIGINT) {
        rl_on_new_line();
        rl_replace_line("myshell> ", 0);
        rl_redisplay();
    }
}

// Fonction de gestion du signal SIGQUIT (Ctrl-\)
void handle_sigquit(int signum) {
    // Ne rien faire pour SIGQUIT
    // Vous pouvez ajouter un comportement personnalisé si nécessaire
}

int main() {
    // Gérer le signal SIGINT en appelant la fonction handle_sigint
    struct sigaction sa_int;
    sa_int.sa_handler = handle_sigint;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);

    // Gérer le signal SIGQUIT en appelant la fonction handle_sigquit
    struct sigaction sa_quit;
    sa_quit.sa_handler = handle_sigquit;
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = 0;
    sigaction(SIGQUIT, &sa_quit, NULL);

    char *input;

    while (1) {
        // Lire une ligne avec Readline
        input = readline("myshell> ");

        // Si l'utilisateur appuie sur Ctrl-D (EOF), quitter le shell
        if (!input) {
            printf("Exiting myshell.\n");
            break;
        }

        // Ajouter la ligne à l'historique
        add_history(input);

        // Faire quelque chose avec la commande, par exemple l'exécuter...

        // Libérer la mémoire allouée par Readline
        free(input);
    }

    return 0;
}
