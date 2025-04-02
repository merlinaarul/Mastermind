programme: main.c vue.c mastermind.c combinaison.c stat-essai.c
	gcc -o mastermind_game main.c vue.c mastermind.c combinaison.c stat-essai.c -Wall  `pkg-config --cflags --libs gtk+-3.0`
	./mastermind_game
