# Commands to check/fix

## Mandatory
### DONE
- [x] heredoc ne fonctionne pas
- [x] `< test.txt cat >test2` ouverture de heredoc non voulu
- [x] `< test.txt cat |wc` gestion des redirection a revoir 
- [x] double retour de prompt suite crash ctrl c ctrl \
- [x] erreur de message dans commande cd double ::
- [x] mv *.txt tes/ ne fonctionne pas 
- [x] fd sortie de commande simple
- [x] revoir gestion des malloc
- [x] free il reste un petit leak a trouver!
- [x] autant de prompt que de minishell sur ctrl-c
- [x] `<<` without args token error to manage
- [x] changer cmd.malloced par cmd.flags avec utilisations des bits au besoin (heredoc)
- [x] <<e cat >te ne fonctionne pas quitte ...
- [x] prend les commande vide .
- [x] $?+$? ne fonctione pas 
- [x] ' single qoute lance une commande 
- [x]  lance une commande au lieu de la skip error tok quote not close
- [x] `|` ouverture heredoc >>error 
- [x] `||` segfault
- [x] <> error 
- [x] cd "" error
- [x] unset une fausse variable segfault
- [x] env disparait au fur et a mesure de l'utilisation
- [x] brace non fonctionnel (ls)&&ls 
- [x] HERE doc with first set write equal limeter close heredoc if string is long
- [x] brace non fonctionnele avec un pipe
- [x] export test = test
- [x] fd open manage sequel
- [x] signal ne fonctionne pas non plus manage sequel
- [x] mettre manage sequel similaire au heredoc (en child process)
- [x] `unset /dasa`

### Builtins
- [ ] `cd` without arguments back to home

### Generalités
- [ ] gestion error redirection a revoir 
- [ ] norminette

## BONUS

## EXTRA

## TOTALK








