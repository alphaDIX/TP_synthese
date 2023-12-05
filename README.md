# TP_synthese (LAB sessions - Ensea microshell)                                                                                                                                          ZART Aurélien - LIN Kévin

Nous avions pour objectif dans ce TP, de construire un microshell en utilisant les nouvelles fonctions découvertes en cours de programmation système. 

EX1:
On commence par afficher le message de bienvenue, pour cela on créee deux constantes (welcome et ensea) et on utilise la fonction 'write' avec comme fd (file descriptor) le standard output càd le code de sortie. 

EX2:
a_ Ensuite, on crée une boucle while infinie afin de construire le prompt (REPL). Pour lire la commande saisie, on utilise la fonction 'read' sur le standard output et on récupère le contenu qu'il lit dans un buffer.

b_ On utilise la fonction 'fork' afin de dupliquer le process parent et crée un process fils. S'il on est dans le process parent, on attend la fin du fils avec 'waitpid' mais s'il on est dans le fils, on éxécute 
la commande avec une fonction 'exec'. Après avoir récupérer la commande, on utilise 'execlp' afin de l'éxécuter. On note que 'execlp' est une fonction exec où l signifie que l'on donne les arguments un par un tandis 
que p précise le fait que la commande est recherchée dans le path. 

c_ Enfin, on se contente de rappeler encore une fois la fonction write avec notre variable ensea afin de remettre en place une nouvelle ligne du prompt.

EX3:
A présent, on rajoute dans la boucle de lecture une condition pour détecter si la commande saisie est 'exit' dans ce cas, on affiche une constante (goodbye) puis on ferme le prompt.

EX4: 
Pour afficher le code de retour, on utilise les fonctions WEXITSTATUS qui renvoie la valeur de sortie d'un process fini et WIFEXITED qui confirme que le process s'est terminé correctement et donc que l'on peut
utiliser WEXITSTATUS. Dans l'hypothèse d'un signal d'interruption qui viendrait bloquer le process et le faire se terminer, on utilise WIFSIGNALED pour savoir s'il y a eu interruption du signal et WTERMSIG pour 
récupérer le nom du signal d'interruption. 


EX5:
On souhaite maintenant afficher le temps d'éxécution. La fonction clock_gettime permet d'importer des structures timespec qui contiennent le temps en secondes et en nanosecondes. On récupère cette mesure
du temps avant et après l'éxécution afin d'avoir le temps d'éxécution. Via une constante 1000, on les ajuste pour obtenir le temps en ms.



