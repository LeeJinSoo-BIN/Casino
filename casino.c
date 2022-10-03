#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <direct.h>

//����
void start_game(int game, int* money);
void end_game(int a);
int done_play();
int select_game();
int best;
int push;
void print_rule();
void clear(int a) {
	for (int k = 0; k < a; k++) {
		printf("\n");
	}
}
struct card {
	int id;
	int value;
	char number[3];
	char symbol[3];
	char face[5];
};
struct rank {
	int score;
	char name[20];
};


//ī��
void card_make(struct card* x) {
	int d = 0;
	for (int k = 101; k <= 413; k++) {
		x[d].id = k;
		if (k % 100 == 13) {
			k += 100;
			k -= 13;
		}
		d++;
	}

}

void shuffle(struct card* x) {
	int d = 0;
	srand(time(NULL));
	struct card tmp;
	for (int k = 0; k < 52; k++) {
		int p = rand() % 52;
		for (int t = 0; t < k; t++) {
			if (x[t].id == x[p].id) {
				d = 1;
				break;
			}
		}
		if (d == 1) {
			k--;
			d = 0;
			continue;
		}
		tmp = x[k];
		x[k] = x[p];
		x[p] = tmp;
	}

}

void card_set(struct card* x) {
	for (int k = 0; k < 52; k++) {
		int a = x[k].id / 100;
		switch (a) {
		case (4):
			strcpy(x[k].symbol, "��");
			break;
		case (3):
			strcpy(x[k].symbol, "��");
			break;
		case(2):
			strcpy(x[k].symbol, "��");
			break;
		case(1):
			strcpy(x[k].symbol, "��");
			break;
		}
		strcpy(x[k].face, x[k].symbol);
		int b = x[k].id % 100;
		if (b == 1) {
			x[k].number[0] = 'A';
			x[k].number[1] = '\0';
			x[k].value = 14;
		}
		else if (b < 10) {
			x[k].number[0] = b + '0';
			x[k].number[1] = '\0';
			x[k].value = b;
		}
		else if (b == 10) {
			x[k].number[0] = '1';
			x[k].number[1] = '0';
			x[k].number[2] = '\0';

			x[k].value = 10;

		}

		else {
			switch (b) {
			case(11):
				x[k].number[0] = 'J';
				x[k].number[1] = '\0';
				x[k].value = 11;
				break;
			case(12):
				x[k].number[0] = 'Q';
				x[k].number[1] = '\0';
				x[k].value = 12;
				break;
			case(13):
				x[k].number[0] = 'K';
				x[k].number[1] = '\0';
				x[k].value = 13;
				break;
			}
		}
		strcat(x[k].face, x[k].number);
	}
}

void card_set_blackjack(struct card* x) {
	card_set(x);
	for (int k = 0; k < 52; k++) {
		int b = x[k].id % 100;
		if (b == 1) {
			x[k].value = 11;
		}
		else if (b < 10) {
			x[k].value = b;
		}
		else if (b == 10) {
			x[k].value = 10;
		}
		else {
			x[k].value = 10;
		}
	}

}
void card_set_baccarat(struct card* x) {
	card_set(x);
	for (int k = 0; k < 52; k++) {
		if (x[k].value == 14) {
			x[k].value = 1;
		}
		int b = x[k].id % 100;
		if (b >= 10) {
			x[k].value = 0;
		}
	}
}
void print_card(struct card* x, int who, int many) {
	if (who == 0) {
		printf("�÷��̾��� ī�� :\n");
	}
	if (who == 1) {
		printf("������ ī�� :\n");
	}
	if (many == 0) {
		printf("����������������������������������������\n");
		printf("��");
		printf(" %s", x[who].face);
		for (int t = 0; t < 7 - strlen(x[1].face); t++) {
			printf(" ");
		}
		printf("��");
		printf("�� ///////��\n");
		printf("��        ���� ///////��\n");
		printf("��    o   ���� ///////��\n");
		printf("��        ���� ///////��\n");
		printf("�� ");
		for (int t = 0; t < 7 - strlen(x[1].face); t++) {
			printf(" ");
		}
		printf("%s��", x[1].face);
		printf("�� ///////��\n");
		printf("����������������������������������������\n");


	}

	else {
		for (int k = 0; k < many; k++) {
			printf("��������������������");
		}
		printf("\n");

		for (int k = 0; k < many; k++) {
			printf("��");
			printf(" %s", x[2 * k + who].face);
			for (int t = 0; t < 7 - strlen(x[2 * k + who].face); t++) {
				printf(" ");
			}
			printf("��");
		}
		printf("\n");

		for (int k = 0; k < many; k++) {
			printf("��        ��");
		}
		printf("\n");
		for (int k = 0; k < many; k++) {
			printf("��    o   ��");
		}
		printf("\n");

		for (int k = 0; k < many; k++) {
			printf("��        ��");
		}
		printf("\n");

		for (int k = 0; k < many; k++) {
			printf("�� ");
			for (int t = 0; t < 7 - strlen(x[2 * k + who].face); t++) {
				printf(" ");
			}
			printf("%s��", x[2 * k + who].face);
		}
		printf("\n");

		for (int k = 0; k < many; k++) {
			printf("��������������������");
		}
		printf("\n");

	}

}

void print_card_back(int many) {
	for (int k = 0; k < many; k++) {
		printf("��������������������");
	}
	printf("\n");
	for (int k = 0; k < 5; k++) {
		for (int k = 0; k < many; k++) {
			printf("�� ///////��");
		}
		printf("\n");
	}
	for (int k = 0; k < many; k++) {
		printf("��������������������");
	}
	printf("\n");
}



void ranking() {

	FILE* ra;
	struct rank* r;
	struct rank tmp;
	int man;
	char n[20];

	_mkdir("data");
	ra = fopen("data\\ranking.txt", "r");
	if (ra == NULL) {
		ra = fopen("data\\ranking.txt", "w");
		fprintf(ra, "%d", 0);
		fclose(ra);
	}
	else {
		fclose(ra);
	}

	getchar();
	printf("��ŷ ���\n");
	printf("NAME : ");
	gets(n);
	ra = fopen("data\\ranking.txt", "r");
	fscanf(ra, "%d", &man);
	r = (struct rank*)malloc((man + 1) * sizeof(struct rank));

	for (int k = 0; k < man; k++) {
		fscanf(ra, "%s %d", r[k].name, &r[k].score);
	}
	fclose(ra);
	strcpy(r[man].name, n);
	r[man].score = best;
	for (int k = 0; k <= man; k++) {
		for (int t = 0; t < man; t++) {
			if (r[t].score < r[t + 1].score) {
				tmp = r[t];
				r[t] = r[t + 1];
				r[t + 1] = tmp;
			}
		}
	}
	clear(30);
	printf("		          �̸�                �ְ�ݾ�\n\n");
	for (int k = 0; k <= man; k++) {
		int l = strlen(r[k].name);
		printf("		%d�� :   %s", k + 1, r[k].name);
		for (int t = 0; t < 20 - l; t++) {
			printf(" ");
		}
		printf("%d����\n", r[k].score);

	}
	clear(10);
	ra = fopen("data\\ranking.txt", "w");
	fprintf(ra, "%d\n", man + 1);
	fclose(ra);
	ra = fopen("data\\ranking.txt", "a");
	for (int k = 0; k <= man; k++) {
		fprintf(ra, "%s %d\n", r[k].name, r[k].score);
	}
	fclose(ra);
	best = 0;
}

void betting(int* money, int* bett) {

	int betting;
	clear(50);
	printf("���� �ڻ� : %d����\n", *money);
	printf("������ �ݾ��� �Է��� �ּ���. (���� : ����) : ");
	scanf("%d", &betting);
	while (1) {
		if (betting > *money) {
			clear(50);
			printf("���� �ڻ��� �ʰ��մϴ�.\n");
			printf("���� �ڻ� : %d����\n", *money);
			printf("���� �ڻ� ������ �ݾ��� �Է��� �ּ���. (���� : ����) : ");
			scanf("%d", &betting);
		}
		else if (betting == 0) {
			clear(50);
			printf("�ڻ� : %d����\n", *money);
			printf("0���� ū �ݾ��� �Է��� �ּ���. (���� : ����) : ");
			scanf("%d", &betting);
		}
		else {
			break;
		}
	}
	*bett = betting;
	*money = *money - betting;
}

//����
void Ace(struct card* x, int turn, int* A) {
	int d = 0;
	for (int k = 0; k < turn; k++) {
		d += x[k * 2].value;
		if (x[k * 2].value == 11) {
			*A = *A + 1;
		}
	}
	if (d > 21) {
		if (*A > 0) {
			for (int k = 0; k < turn; k++) {
				if (x[k * 2].value == 11) {
					x[k * 2].value = 1;
					break;
				}
			}
			Ace(x, turn, A);
		}
	}
}
void Bce(struct card* x, int turn, int* A) {
	int d = 0;
	for (int k = 0; k < turn; k++) {
		d += x[k * 2 + 1].value;
		if (x[k * 2 + 1].value == 11) {
			*A = *A + 1;
		}
	}
	if (d > 21) {
		if (*A > 0) {
			for (int k = 0; k < turn; k++) {
				if (x[k * 2 + 1].value == 11) {
					x[k * 2 + 1].value = 1;
					break;
				}
			}
			Bce(x, turn, A);
		}
	}
}
int score(struct card* x, int turn, int who) {
	int d = 0;
	int A = 0;
	int z = 0;
	if (who == 1) {
		Ace(x, turn, &A);
		for (int k = 0; k < turn; k++) {
			d += x[k * 2].value;
		}
		if (d > 21) {
			return(1);
		}
		else if (turn == 2 && d == 21) {
			return(2);
		}
		else {
			return(0);
		}

	}
	if (who == 2) {
		Bce(x, turn, &A);
		for (int k = 0; k < turn; k++) {
			d += x[k * 2 + 1].value;
		}
		if (d > 21) {
			return(2);
		}
		else if (d > 16) {
			return(1);
		}
		else {
			return(0);
		}
	}
	if (who == 3) {
		for (int k = 0; k < turn; k++) {
			d += x[k * 2].value;
		}
		return(d);
	}
	if (who == 4) {
		for (int k = 0; k < turn; k++) {
			d += x[k * 2 + 1].value;
		}
		return(d);
	}
}
int black(struct card* x) {
	char a[100];
	printf("���͸� �����ּ���.");
	getchar();
	gets(a);
	clear(30);
	print_card(x, 1, 2);
	if (x[1].value + x[3].value == 21) {
		printf("���� ���� : Black Jack!\n");
	}
	else {
		printf("���� ���� : %d\n", score(x, 1, 4));
	}
	clear(5);
	print_card(x, 0, 2);
	printf("�÷��̾� ���� : Black Jack!\n");
	if (x[1].value + x[3].value == 21) {
		clear(2);
		return(4);
	}
	else {
		return(5);
	}
}
int hit_or_stay(int turn) {
	int hs;
	while (1) {
		if (turn == 0) {
			printf("HIT : 1           STAY : 2           SURRENDER : 3\n");
			scanf("%d", &hs);
			if (hs == 1 || hs == 2 || hs == 3) {
				break;
			}
			else {
				printf("1 �Ǵ� 2 �Ǵ� 3 �� �Է� �����մϴ�.\n");
			}
		}
		else {
			printf("HIT : 1           STAY : 2\n");
			scanf("%d", &hs);
			if (hs == 1 || hs == 2) {
				break;
			}
			else {
				printf("1�� 2�� �Է� �����մϴ�.\n");
			}
		}
	}
	return(hs);
}
int stay(struct card* x, int* player_turn, int* dealer_turn) {
	int p, d;
	char a[100];
	*dealer_turn = *dealer_turn + 1;
	while (1) {
		*dealer_turn = *dealer_turn + 1;
		printf("������ ī�� Ȯ��\n\n\n\n\n���͸� �Է����ּ���.");
		gets(a);
		clear(50);
		d = score(x, *dealer_turn, 2);
		print_card(x, 1, *dealer_turn);
		if (d != 2) {
			printf("���� ���� : %d", score(x, *dealer_turn, 4));
		}
		else if (d == 2) {
			printf("���� ���� : BUST!");
		}
		clear(6);
		print_card(x, 0, *player_turn);
		printf("�÷��̾� ���� : %d\n", score(x, *player_turn, 3));
		clear(2);
		if (d != 0) {
			break;
		}
		clear(2);
	}
	if (d == 1) {
		p = score(x, *player_turn, 3);
		d = score(x, *dealer_turn, 4);
		if (p > d) {
			return(0);
		}
		else if (p < d) {
			return(1);
		}
		else {
			return(4);
		}
	}
	else if (d == 2) {
		return(0);
	}
}
int turn(struct card* x, int* player_turn, int* dealer_turn) {

	int bust;
	int hs;
	clear(50);
	print_card(x, 1, *dealer_turn);
	clear(6);
	print_card(x, 0, *player_turn);


	bust = score(x, *player_turn, 1);
	if (bust == 0) {
		printf("�÷��̾� ���� : %d\n", score(x, *player_turn, 3));
		clear(8);
		hs = hit_or_stay(*player_turn);
		if (hs == 1) {
			*player_turn = *player_turn + 1;
			turn(x, player_turn, dealer_turn);
		}
		else if (hs == 3) {
			return(2);//������
		}
		else {
			return(stay(x, player_turn, dealer_turn));//��0 ��1 ��4
		}
	}
	else if (bust == 2) {
		printf("�÷��̾� ���� : Black Jack!\n");
		clear(9);
		return(black(x));
	}
	else {
		printf("�÷��̾� ���� : BUST!\n\n\n");
		return(3);//����Ʈ
	}

}
int how_much(int* money1, int bet, int result) {

	char tmp[100];
	switch (result) {
	case(0):
		*money1 = *money1 + bet * 2;
		printf("YOU WIN");
		clear(2);
		printf("���� �ݾ� : %d����\n", bet);
		printf("            %d + %d\n", *money1 - bet, bet);
		printf("���� �ڻ� : %d����\n\n", *money1);
		break;
	case(1):
		*money1 = *money1;
		printf("YOU LOSE");
		clear(2);
		printf("���� �ݾ� : %d����\n", bet);
		printf("            %d - %d\n", *money1 + bet, bet);
		printf("���� �ڻ� : %d����\n\n", *money1);
		break;
	case(2):
		*money1 = *money1 + bet / 2;
		clear(1);
		printf("SURRENDER");
		clear(2);
		printf("���� �ݾ� : %d����\n", bet);
		printf("            %.0f + %d\n", *money1 - bet * 0.5, bet / 2);
		printf("���� �ڻ� : %d����\n", *money1);
		getchar();
		break;
	case(3):
		*money1 = *money1;
		printf("YOU BUST");
		clear(2);
		printf("���� �ݾ� : %d����\n", bet);
		printf("            %d - %d\n", *money1 + bet, bet);
		printf("���� �ڻ� : %d����\n\n", *money1);
		getchar();
		break;
	case(4):
		*money1 = *money1 + bet;
		printf("DRAW");
		clear(2);
		printf("���� �ݾ� : %d����\n", bet);
		printf("���� �ڻ� : %d����\n\n\n", *money1);
		break;
	case(5):
		*money1 = *money1 + bet * 2.5;
		clear(2);
		printf("BLACK JACK!!");
		clear(2);
		printf("���� �ݾ� : %d����\n", bet);
		printf("            %.0f + %.0f\n", *money1 - bet * 1.5, bet * 1.5);
		printf("���� �ڻ� : %d����\n\n", *money1);
		break;
	}
	printf("���͸� �Է����ּ���");
	gets(tmp);
	if (best < *money1) {
		best = *money1;
	}
	if (*money1 > 0) {
		return(done_play());
	}
	else {
		return(3);
	}

}
void black_jack(int* money) {
	struct card x[52];
	card_make(x);
	shuffle(x);
	card_set_blackjack(x);
	int result;
	int bet;
	int p_turn = 2;
	int d_turn = 0;
	int game;
	betting(money, &bet);
	result = turn(x, &p_turn, &d_turn);
	game = (how_much(money, bet, result));
	if (game == 1) {
		black_jack(money);
	}
	else if (game == 2) {
		int gam = select_game();
		start_game(gam, money);
	}
	else {
		end_game(1);
	}
}


//��ī��
void bet_baccarat(int* money, int* bet, int* whom) {
	int a;
	clear(50);
	printf("�÷��̾� : 1           ���� : 2           Tie : 3          Pair : 4\n");
	printf("���� ����� �������ּ��� : ");
	scanf("%d", &a);
	while (1) {
		if (a == 1 || a == 2 || a == 3 || a == 4) {
			break;
		}
		clear(50);
		printf("��� �� �ϳ��� �����Ͽ� �ּ���\n");
		printf("�÷��̾� : 1           ���� : 2           Tie : 3          Pair : 4\n");
		printf("���� ����� �������ּ��� : ");
		scanf("%d", &a);
	}
	clear(50);
	printf("���� ��� : ");
	if (a == 1) {
		printf("�÷��̾�\n");
	}
	else if (a == 2) {
		printf("����\n");
	}
	else if (a == 3) {
		printf("Tie\n");
	}
	else {
		printf("Pair\n");
	}
	printf("���� �ڻ� : %d����\n", *money);
	printf("���� �ݾ��� �Է����ּ���(���� : ����) : ");
	scanf("%d", bet);
	while (1) {
		if (*bet > *money) {
			clear(50);
			printf("���� ��� : ");
			if (a == 1) {
				printf("�÷��̾�\n");
			}
			else if (a == 2) {
				printf("����\n");
			}
			else if (a == 3) {
				printf("Tie\n");
			}
			else {
				printf("Pair\n");
			}
			printf("���� �ڻ� : ����%d\n", *money);
			printf("���� �ݾ׺��� ���� ���� �Է����ּ���(���� : ����) :");
			scanf("%d", bet);
		}
		else if (*bet == 0) {
			clear(50);
			printf("���� ��� : ");
			if (a == 1) {
				printf("�÷��̾�\n");
			}
			else if (a == 2) {
				printf("����\n");
			}
			else if (a == 3) {
				printf("Tie\n");
			}
			else {
				printf("Pair\n");
			}
			printf("���� �ڻ� : ����%d\n", *money);
			printf("0���� ū �ݾ��� �Է����ּ���(���� : ����) : ");
			scanf("%d", bet);
		}
		else {
			break;
		}
	}
	*whom = a;
}
int score_baccarat(struct card* x, int who, int many) {
	int a = 0;
	for (int k = 0; k < many; k++) {
		a += x[k * 2 + who].value;
		a %= 10;
	}
	return a;
}
void print_baccarat(struct card* x, int pt, int dt, int ds, int ps) {

	clear(50);
	print_card(x, 1, dt);
	printf("���� ���� : %d", ds);
	clear(6);
	print_card(x, 0, pt);
	printf("�÷��̾� ���� : %d", ps);
	clear(2);

}
void baccarat(int* money) {
	struct card x[52];
	card_make(x);
	shuffle(x);
	card_set_baccarat(x);
	int betting = 0;
	int bet_whom = 0;
	int dt = 2;
	int pt = 2;
	int ds = 0;
	int ps = 0;
	int casee = 0;
	char d[100];
	int a;

	bet_baccarat(money, &betting, &bet_whom);

	ds = score_baccarat(x, 1, dt);
	ps = score_baccarat(x, 0, pt);

	print_baccarat(x, pt, dt, ds, ps);
	printf("���͸� �����ּ���");
	gets(d);

	print_baccarat(x, pt, dt, ds, ps);
	clear(2);
	if (ps == 8 || ps == 9 || ds == 8 || ds == 9) {
		printf("NATURAL\n\n");
		casee = 0;
	}
	else if (0 <= ps && ds <= 5) {
		printf("�÷��̾� : HIT\n\n");
		pt++;
		casee = 1;
	}
	else if ((ps == ds) && (bet_whom == 4)) {
		casee = 3;
	}
	else {
		printf("�÷��̾� : STAND\n\n");
		casee = 2;
	}
	clear(2);
	printf("���͸� �����ּ���");
	gets(d);

	ds = score_baccarat(x, 1, dt);
	ps = score_baccarat(x, 0, pt);


	print_baccarat(x, pt, dt, ds, ps);
	clear(2);

	if (casee == 0) {
		printf("NATURAL\n\n");
	}
	else if (casee == 3) {

	}
	else {
		if (casee == 1) {
			if (0 <= ds && ds <= 2) {
				printf("���� : HIT\n\n");
				dt++;
			}
			else if (ds == 3) {
				if (0 <= x[4].value && x[4].value <= 7) {
					printf("���� : HIT\n\n");
					dt++;
				}
				else {
					printf("���� : STAND\n\n");
				}
			}
			else if (ds == 4) {
				if (2 <= x[4].value && x[4].value <= 7) {
					printf("���� : HIT\n\n");
					dt++;
				}
				else {
					printf("���� : STAND\n\n");
				}
			}
			else if (ds == 5) {
				if (4 <= x[4].value && x[4].value <= 7) {
					printf("���� : HIT\n\n");
					dt++;
				}
				else {
					printf("���� : STAND\n\n");
				}
			}
			else if (ds == 6) {
				if (6 <= x[4].value && x[4].value <= 7) {
					printf("���� : HIT\n\n");
					dt++;
				}
				else {
					printf("���� : STAND\n\n");
				}
			}
			else if (ds == 7) {
				printf("���� : STAND\n\n");
			}
		}
		else if (casee == 2) {
			if (0 <= ds && ds <= 5) {
				printf("���� : HIT\n\n");
				dt++;
			}
			else {
				printf("���� : STAND\n\n");
			}
		}
		clear(2);
		printf("���͸� ���� ����� Ȯ���ϼ���");
		gets(d);
	}



	ds = score_baccarat(x, 1, dt);
	ps = score_baccarat(x, 0, pt);

	print_baccarat(x, pt, dt, ds, ps);

	if (bet_whom == 1) {
		printf("���ô�� : �÷��̾�     �ݾ� : %d����\n", betting);
	}
	else if (bet_whom == 2) {
		printf("���ô�� : ����         �ݾ� : %d����\n", betting);
	}
	else if (bet_whom == 3) {
		printf("���ô�� : TIE         �ݾ� : %d����\n", betting);
	}
	else {
		printf("���ô�� : PAIR       �ݾ� : %d����\n", betting);
	}
	if (ps > ds) {
		printf("��� : �÷��̾� �¸�\n");
		if (bet_whom == 1) {
			printf("            %d + %d\n", *money, betting);
			*money = *money + betting;
			printf("���� �ڻ� : %d����\n", *money);
		}
		else {
			printf("            %d - %d\n", *money, betting);
			*money = *money - betting;
			printf("���� �ڻ� : %d����\n", *money);
		}
	}
	else if (ds > ps) {
		printf("��� : ���� �¸�\n");
		if (bet_whom == 2) {
			printf("            %d + %d\n", *money, betting);
			*money = *money + betting;
			printf("���� �ڻ� : %d����\n", *money);
		}
		else {
			printf("            %d - %d\n", *money, betting);
			*money = *money - betting;
			printf("���� �ڻ� : %d����\n", *money);
		}
	}
	else {
		if (casee == 3) {
			printf("��� : PAIR\n");
			if (bet_whom == 4) {
				printf("            %d + %d\n", *money, betting * 11);
				*money = *money + betting * 11;
				printf("���� �ڻ� : %d\n", *money);
			}
		}
		else {
			printf("��� : TIE\n");
			if (bet_whom == 3) {
				printf("            %d + %d\n", *money, betting * 8);
				*money = *money + betting * 8;
				printf("���� �ڻ� : %d\n", *money);
			}
			else {
				printf("            %d - %d\n", *money, betting);
				*money = *money - betting;
				printf("���� �ڻ� : %d\n", *money);
			}
		}
	}
	printf("\n");
	printf("���͸� �����ּ���");
	gets(d);
	if (best < *money) {
		best = *money;
	}

	if (*money > 0) {
		a = done_play();
		if (a == 1) {
			baccarat(money);
		}
		else {
			int gam = select_game();
			start_game(gam, money);
		}
	}
	else {
		printf("���͸� �����ּ���");
		gets(d);
		end_game(1);
	}
}


//����ī��
int count(struct card* x, int who) {
	char val[50];
	int d[3];
	int f[3];
	int tmp;
	int score;
	for (int k = 0; k < 3; k++) {
		d[k] = x[k * 2 + who].id;
		if (x[k * 2 + who].value == 14) {
			d[k] += 13;
		}
		f[k] = k * 2 + who;
	}
	for (int k = 0; k < 3; k++) {
		for (int t = 0; t < 2; t++) {
			if (d[t] % 100 < d[t + 1] % 100) {

				tmp = d[t];
				d[t] = d[t + 1];
				d[t + 1] = tmp;
				tmp = f[t];
				f[t] = f[t + 1];
				f[t + 1] = tmp;
			}
		}
	}
	for (int k = 0; k < 3; k++) {
		for (int t = 0; t < 2; t++) {
			if (d[t] % 100 == d[t + 1] % 100 && d[t] - (d[t] % 100) < d[t + 1] - (d[t + 1] % 100)) {
				tmp = d[t];
				d[t] = d[t + 1];
				d[t + 1] = tmp;
				tmp = f[t];
				f[t] = f[t + 1];
				f[t + 1] = tmp;
			}
		}
	}
	strcpy(val, x[f[0]].number);
	strcat(val, x[f[0]].symbol);
	strcat(val, " ");
	strcat(val, "ž");
	score = 1000 + x[f[0]].value * 10 + x[f[0]].id / 100;
	if (d[0] % 100 == d[1] % 100) {
		strcpy(val, x[f[0]].number);
		strcat(val, x[f[0]].symbol);
		strcat(val, " ");
		strcat(val, "�� �о�");
		score = 2000 + x[f[0]].value * 10 + x[f[0]].id / 100;
	}
	if (d[1] % 100 == d[2] % 100) {
		strcpy(val, x[f[1]].number);
		strcat(val, x[f[1]].symbol);
		strcat(val, " ");
		strcat(val, "�� �о�");
		score = 2000 + x[f[1]].value * 10 + x[f[1]].id / 100;
	}
	if (d[0] - d[0] % 100 == d[1] - d[1] % 100 && d[1] - d[1] % 100 == d[2] - d[2] % 100) {
		strcpy(val, x[f[0]].number);
		strcat(val, x[f[0]].symbol);
		strcat(val, " ");
		strcat(val, "�÷���");
		score = 3000 + x[f[0]].value * 10 + x[f[0]].id / 100;
	}
	if (d[0] - d[0] % 100 == 14) {
		int n[3];
		n[0] = d[1];
		n[1] = d[2];
		n[2] = d[0] - 13;

		if (n[0] % 100 == n[1] % 100 + 1 && n[0] % 100 == n[2] % 100 + 2) {
			strcpy(val, x[f[1]].number);
			strcat(val, x[f[1]].symbol);
			strcat(val, " ");
			strcat(val, "��Ʈ����Ʈ");
			score = 4000 + x[f[1]].value * 10 + x[f[0]].id / 100;
		}
	}
	if (d[0] % 100 == d[1] % 100 + 1 && d[0] % 100 == d[2] % 100 + 2) {
		strcpy(val, x[f[0]].number);
		strcat(val, x[f[0]].symbol);
		strcat(val, " ");
		strcat(val, "��Ʈ����Ʈ");
		score = 4000 + x[f[0]].value * 10 + x[f[0]].id / 100;
	}
	if (d[0] % 100 == d[1] % 100 && d[0] % 100 == d[2] % 100) {
		strcpy(val, x[f[0]].number);
		strcat(val, x[f[0]].symbol);
		strcat(val, " ");
		strcat(val, "Ʈ����");
		score = 5000 + x[f[0]].value * 10 + x[f[0]].id / 100;
	}
	if (d[0] - d[0] % 100 == 14) {
		int n[3];
		n[0] = d[1];
		n[1] = d[2];
		n[2] = d[0] - 13;

		if ((n[0] % 100 == n[1] % 100 + 1 && n[0] % 100 == n[2] % 100 + 2) && (n[0] - n[0] % 100 == n[1] - n[1] % 100 && n[1] - n[1] % 100 == n[2] - n[2] % 100)) {
			strcpy(val, x[f[1]].number);
			strcat(val, x[f[1]].symbol);
			strcat(val, " ");
			strcat(val, "��Ʈ����Ʈ �÷���");
			score = 6000 + x[f[1]].value * 10 + x[f[1]].id / 100;
		}
	}
	if ((d[0] % 100 == d[1] % 100 + 1 && d[0] % 100 == d[2] % 100 + 2) && (d[0] - d[0] % 100 == d[1] - d[1] % 100 && d[1] - d[1] % 100 == d[2] - d[2] % 100)) {
		strcpy(val, x[f[0]].number);
		strcat(val, x[f[0]].symbol);
		strcat(val, " ");
		strcat(val, "��Ʈ����Ʈ �÷���");
		score = 6000 + x[f[0]].value * 10 + x[f[0]].id / 100;
	}
	printf(" %s\n", val);

	return(score);
}
void get_card(struct card* x) {
	clear(50);
	printf("������ ī�� :\n");
	print_card_back(3);
	clear(5);
	print_card(x, 0, 3);
	count(x, 0);

}
int what_do() {
	int hs;
	while (1) {
		printf("PLAY : 1            FOLD : 2\n");
		scanf("%d", &hs);
		getchar();
		if (hs == 1 || hs == 2) {
			break;
		}
		else {
			printf("1�� 2�� �Է� �����մϴ�.\n");
		}

	}
	return(hs);
}
void three_result(int state, int* money, int bet) {
	char tmp[50];
	if (state == 1) {
		printf("WIN!\n\n");
		printf("�ʱ� �ڻ� : %d����\n", *money + bet);
		printf("���� �ݾ� : %d����        PUSH �ݾ� : %d����\n", bet, push);
		printf("            %d + %d + %d\n", *money + bet, bet, push);
		*money = *money + bet * 2 + push;
		printf("���� �ڻ� : %d����\n", *money);
		push = 0;
	}
	else if (state == 2) {
		printf("LOSE!\n\n");
		printf("�ʱ� �ڻ� : %d����\n", *money + bet);
		printf("���� �ݾ� : %d����      PUSH �ݾ� : %d����\n", bet, push);
		printf("            %d - %d\n", *money + bet, bet);
		push = 0;
		printf("���� �ڻ� : %d����      PUSH : %d����\n", *money, push);

	}
	else if (state == 3) {
		printf("PUSH!\n\n");
		printf("�ʱ� �ڻ� : %d����\n", *money + bet);
		printf("���� �ݾ� : %d����      PUSH �ݾ� : %d����\n", bet, push);
		push += bet * 0.5;
		printf("            %d - %d    PUSH = %d\n", *money + bet, bet / 2, push);
		*money += bet * 0.5;
		printf("���� �ڻ� : %d����          PUSH : %d����\n", *money, push);

	}
	else {
		printf("FOLD!\n\n");
		printf("�ʱ� �ڻ� : %d\n", *money + bet);
		printf("���� �ݾ� : %d����      PUSH �ݾ� : %d����\n", bet, push);
		printf("            %d - %d + %d\n", *money + bet, bet, bet / 2);
		*money += bet * 0.5;
		printf("���� �ڻ� : %d����      PUSH : %d����\n", *money, push);

	}
	printf("���͸� �����ּ���.\n");
	gets(tmp);
	printf("\n");
}
void three_card(int* money) {
	struct card x[52];
	int bet;
	int what;
	int d_s;
	int p_s;
	int a;
	char tmp[50];
	card_make(x);
	shuffle(x);
	card_set(x);
	betting(money, &bet);
	get_card(x);
	clear(9);
	what = what_do();
	if (what == 1) {
		clear(50);
		print_card(x, 1, 3);
		d_s = count(x, 1);
		clear(4);
		print_card(x, 0, 3);
		p_s = count(x, 0);
		clear(2);
		if (d_s >= 1121) {
			if (p_s > d_s) {
				three_result(1, money, bet);//��
			}
			else {
				three_result(2, money, bet);//��
			}
		}
		else {
			three_result(3, money, bet);//��
		}
	}
	else {
		get_card(x);
		clear(2);
		three_result(4, money, bet);//��
	}

	if (*money > best) {
		best = *money;
	}
	if (*money > 0) {
		a = done_play();
		if (a == 1) {
			three_card(money);
		}
		else {
			int gam = select_game();
			start_game(gam, money);
		}
	}
	else {
		end_game(1);
	}

}


//�渶
void run_horse(int step1, int step2, int step3, int step4, int delay, int len) {

	int end = len;
	clear(50);
	for (int k = 0; k < step1; k++) {
		printf(" ");
	}
	printf("               , --, ");
	for (int k = 0; k < end - step1; k++) {
		printf(" ");
	}
	printf("|     |\n");
	for (int k = 0; k < step1; k++) {
		printf(" ");
	}
	printf("        _ ___ / / \\|");
	for (int k = 0; k < end - step1 + 1; k++) {
		printf(" ");
	}
	printf("|     |\n");
	for (int k = 0; k < step1; k++) {
		printf(" ");
	}
	printf("   ,;'( )__, )     ~ ");
	for (int k = 0; k < end - step1; k++) {
		printf(" ");
	}
	printf("|     |\n");
	for (int k = 0; k < step1; k++) {
		printf(" ");
	}
	printf("  //    //   '--;    ");
	for (int k = 0; k < end - step1; k++) {
		printf(" ");
	}
	printf("|     |\n");
	for (int k = 0; k < step1; k++) {
		printf(" ");
	}
	printf("  '      \\    |  ^  ");
	for (int k = 0; k < end - step1 + 1; k++) {
		printf(" ");
	}
	printf("|     |\n");
	for (int k = 0; k < step1; k++) {
		printf(" ");
	}
	printf("         ^    ^      ");
	for (int k = 0; k < end - step1; k++) {
		printf(" ");
	}
	printf("|  G  |\n");

	for (int k = 0; k < end + 21; k++) {
		printf(" ");
	}
	printf("|     |\n");



	for (int k = 0; k < step2; k++) {
		printf(" ");
	}
	printf("               .\''\"");
	for (int k = 0; k < end - step2 + 2; k++) {
		printf(" ");
	}
	printf("|     |\n");
	for (int k = 0; k < step2; k++) {
		printf(" ");
	}
	printf("    ._. - .___.' (`\\");
	for (int k = 0; k < end - step2 + 1; k++) {
		printf(" ");
	}
	printf("|     |\n");
	for (int k = 0; k < step2; k++) {
		printf(" ");
	}
	printf("   //(          ( `' ");
	for (int k = 0; k < end - step2; k++) {
		printf(" ");
	}
	printf("|  O  |\n");
	for (int k = 0; k < step2; k++) {
		printf(" ");
	}
	printf(" '/ )\\ ).__. )      ");
	for (int k = 0; k < end - step2 + 1; k++) {
		printf(" ");
	}
	printf("|     |\n");
	for (int k = 0; k < step2; k++) {
		printf(" ");
	}
	printf(" ' <' `\\ ,_/ '\\    ");
	for (int k = 0; k < end - step2 + 2; k++) {
		printf(" ");
	}
	printf("|     |\n");
	for (int k = 0; k < step2; k++) {
		printf(" ");
	}
	printf("    `   \\      \\   ");
	for (int k = 0; k < end - step2 + 2; k++) {
		printf(" ");
	}
	printf("|     |\n");

	for (int k = 0; k < end + 21; k++) {
		printf(" ");
	}
	printf("|  A  |\n");

	for (int k = 0; k < step3; k++) {
		printf(" ");
	}
	printf("        _____,,;;;`;;");
	for (int k = 0; k < end - step3; k++) {
		printf(" ");
	}
	printf("|     |\n");
	for (int k = 0; k < step3; k++) {
		printf(" ");
	}
	printf("    , ~(  )  , )~~\\|");
	for (int k = 0; k < end - step3 + 1; k++) {
		printf(" ");
	}
	printf("|     |\n");
	for (int k = 0; k < step3; k++) {
		printf(" ");
	}
	printf("    '  / / --`--,    ");
	for (int k = 0; k < end - step3; k++) {
		printf(" ");
	}
	printf("|     |\n");
	for (int k = 0; k < step3; k++) {
		printf(" ");
	}
	printf("      /  \\   |  '   ");
	for (int k = 0; k < end - step3 + 1; k++) {
		printf(" ");
	}
	printf("|  L  |\n");
	for (int k = 0; k < end + 21; k++) {
		printf(" ");
	}
	printf("|     |\n");
	for (int k = 0; k < step4; k++) {
		printf(" ");
	}
	printf("               , --, ");
	for (int k = 0; k < end - step4; k++) {
		printf(" ");
	}
	printf("|     |\n");
	for (int k = 0; k < step4; k++) {
		printf(" ");
	}
	printf("        _ ___ / / \\|");
	for (int k = 0; k < end - step4 + 1; k++) {
		printf(" ");
	}
	printf("|     |\n");
	for (int k = 0; k < step4; k++) {
		printf(" ");
	}
	printf("       ; ()__, )     ");
	for (int k = 0; k < end - step4; k++) {
		printf(" ");
	}
	printf("|     |\n");
	for (int k = 0; k < step4; k++) {
		printf(" ");
	}
	printf("      ;  //   '--;   ");
	for (int k = 0; k < end - step4; k++) {
		printf(" ");
	}
	printf("|     |\n");
	for (int k = 0; k < step4; k++) {
		printf(" ");
	}
	printf("         \\     )    ");
	for (int k = 0; k < end - step4 + 1; k++) {
		printf(" ");
	}
	printf("|     |\n");
	for (int k = 0; k < step4; k++) {
		printf(" ");
	}
	printf("          ^    ^     ");
	for (int k = 0; k < end - step4; k++) {
		printf(" ");
	}
	printf("|     |\n");
	printf("\n");


	Sleep(delay);

}
void bet_horse() {

	clear(50);
	printf("\n");
	printf("\n");
	printf("                                     , --,                     .''                    , --,        \n");
	printf("        _____,,;;;`;;	       _ ___/ / \\|         ._. - .___.' (`\\ 	       _ ___ / / \\|       \n");
	printf("    , ~(  ),  )~~\\ |    , ; '( )__, )    ~          //(        ( `'         ;( )__,  )            \n");
	printf("     ' / / --`--,            //  // '--;          '/ )\\ ).__. )            ; //   '--;            \n");
	printf("      /  \\   |  '        '   \\   |     ^          ' <'`\\ ,_ / '\\              \\   |           \n");
	printf("      ^   ^  ^               ^   ^                  ^   \\       \\             ^   ^              \n");
	printf("\n");
	printf("         1�� ��                2�� ��                   3�� ��                4�� ��\n");

}
void horse_run(int* money) {

	int horse = 0;
	int pick = 0;
	int bet = 0;
	char b[50];
	clear(50);
	system("mode con cols=150 lines=35");
	bet_horse();
	printf("\n                             ������ ���� �������ּ���.\n\n");
	scanf("%d", &horse);
	getchar();
	while (1) {
		if (horse == 1) {
			pick = 2;
			break;
		}
		if (horse == 2) {
			pick = 3;
			break;
		}
		if (horse == 3) {
			pick = 5;
			break;
		}
		if (horse == 4) {
			pick = 7;
			break;
		}
		else {
			bet_horse();
			printf("\n                             1~4�� �� �߿����� �������ּ���.\n");
			scanf("%d", &horse);
			getchar();
		}

	}

	betting(money, &bet);
	clear(50);
	run_horse(0, 0, 0, 0, 500, 100);
	printf("\n���͸� ������ �渶�� �����մϴ�.");
	getchar();
	gets(b);



	int h1 = 0;
	int h2 = 0;
	int h3 = 0;
	int h4 = 0;
	int win = 1;
	while (1) {
		srand(time(NULL));
		run_horse(h1, h2, h3, h4, 500, 100);
		if (h1 > 100) {
			win *= 2;
			printf("1�� �� ��� !!\n");
		}
		if (h2 > 100) {
			win *= 3;
			printf("2�� �� ��� !!\n");
		}
		if (h3 > 100) {
			win *= 5;
			printf("3�� �� ��� !!\n");
		}
		if (h4 > 100) {
			win *= 7;
			printf("4�� �� ��� !!\n");
		}
		if (win >= 2) {
			printf("\n");
			break;
		}
		int p1 = rand() % 10;
		int p2 = rand() % 10;
		int p3 = rand() % 10;
		int p4 = rand() % 10;
		h1 += p1;
		h2 += p2;
		h3 += p3;
		h4 += p4;

	}
	if (win % pick == 0) {
		printf("������ �� : %d�� ��\n", horse);
		printf("���� !\n");
		printf("�ʱ� �ڻ� : %d����\n", *money + bet);
		printf("���� �ݾ� : %d����\n", bet);
		printf("            %d + %d\n", *money + bet, bet * 2);
		*money = *money + 3 * bet;
		printf("���� �ڻ� : %d����\n", *money);




	}
	else {

		printf("������ �� : %d�� ��\n", horse);
		printf("������\n");
		printf("���� �ڻ� : %d����\n", *money + bet);
		printf("���� �ݾ� : %d����\n", bet);
		printf("            %d - %d\n", *money + bet, bet);
		printf("���� �ڻ� : %d����\n", *money);
	}

	printf("\n���͸� �����ּ���");
	gets(b);

	if (*money > best) {
		best = *money;
	}
	if (*money > 0) {
		int a = done_play();
		if (a == 1) {
			horse_run(money);
		}
		else {
			int gam = select_game();
			start_game(gam, money);
		}
	}
	else {
		printf("\n���͸� �����ּ���");
		gets(b);
		end_game(1);
	}

}



//�⺻
int select_game() {
	int a;
	system("mode con cols=103 lines=35");
	clear(50);
	printf("                             �÷����� ������ �������ּ���\n\n");
	printf("     ���� : 1           ��ī�� : 2          ����ī�� ��Ŀ : 3\n");
	printf("     �渶 : 4             ���� ��Ģ : 5       ���� : 6\n");
	scanf("%d", &a);
	while (1) {
		if (a == 1 || a == 2 || a == 3 || a == 4 || a == 6) {
			break;
		}
		else if (a == 5) {
			print_rule();
			clear(50);
			printf("                             �÷����� ������ �������ּ���\n\n");
			printf("     ���� : 1           ��ī�� : 2          ����ī�� ��Ŀ : 3\n");
			printf("     �渶 : 4             ���� ��Ģ : 5       ���� : 6\n");
			scanf("%d", &a);
		}
		else {
			clear(50);
			printf("     ���� : 1           ��ī�� : 2          ����ī�� ��Ŀ : 3\n");
			printf("     �渶 : 4             ���� ��Ģ : 5       ���� : 6\n");
			printf("��� �߿����� ����ּ���\n");
			scanf("%d", &a);
		}

	}
	return(a);
}
void start_game(int game, int* money) {
	system("mode con cols=103 lines=35");
	clear(50);
	char a[100];
	if (game == 1) {
		clear(50);
		printf("                                    !! B L A C K        J A C K !!\n");
		clear(5);
		printf("					 ������ �����մϴ�.");
		clear(10);
		printf("					 ���͸� �����ּ���.");
		getchar();
		gets(a);
		black_jack(money);
	}
	else if (game == 2) {
		clear(50);
		printf("                                       !! B A C C A R A T !!\n");
		clear(5);
		printf("					 ������ �����մϴ�.");
		clear(10);
		printf("					 ���͸� �����ּ���.");
		getchar();
		gets(a);
		baccarat(money);
	}
	else if (game == 3) {
		clear(50);
		printf("                                !! T H R E E   C A R D   P O K E R !!\n");
		clear(5);
		printf("					 ������ �����մϴ�.");
		clear(10);
		printf("					 ���͸� �����ּ���.");
		getchar();
		gets(a);
		three_card(money);
	}
	else if (game == 4) {
		clear(50);
		printf("                                    !! ��                  �� !!\n");
		clear(5);
		printf("					 ������ �����մϴ�.");
		clear(10);
		printf("					 ���͸� �����ּ���.");
		getchar();
		gets(a);
		horse_run(money);
	}
	else if (game == 5) {
		print_rule();
	}
	else if (game == 6) {
		end_game(2);
	}
}
void end_game(int a) {
	system("mode con cols=103 lines=35");
	if (a == 1) {
		clear(50);
		printf("                                             �Ļ�");
		clear(15);
	}
	else if (a == 2) {
		clear(50);
		printf("                                              ��");
		clear(15);
	}
	if (best > 1000) {
		ranking();
	}
}
int done_play() {

	system("mode con cols=103 lines=35");
	clear(50);
	int a;
	printf("����ϱ� : 1                 �ٸ� ���� : 2      \n");
	scanf("%d", &a);
	getchar();
	while (1) {
		if (a == 1 || a == 2) {
			break;
		}
		else {
			printf("1�� 2�߿����� ����ּ���\n");
			printf("����ϱ� : 1                 �ٸ� ���� : 2      \n");
			scanf("%d", &a);
			getchar();
		}
	}
	return(a);
}

void print_rule() {
	int game = 0;
	while (1) {

		clear(50);
		printf("                             ��Ģ�� �� ������ �������ּ���.\n\n");
		printf("     ���� : 1           ��ī�� : 2       ����ī�� ��Ŀ : 3\n");
		printf("     �渶 : 4             ���ư��� : 5\n");
		scanf("%d", &game);
		getchar();
		while (1) {
			if (game == 1 || game == 2 || game == 3 || game == 4) {
				break;
			}
			else if (game == 5) {
				return;
			}
			else {
				clear(50);
				printf("                             ��� �߿����� ����ּ���.\n\n");
				printf("     ���� : 1           ��ī�� : 2       ����ī�� ��Ŀ : 3\n");
				printf("     �渶 : 4             ���ư��� : 4\n");
				scanf("%d", &game);
				getchar();
			}
		}

		switch (game) {
		case(1):
			clear(50);
			printf("					 ����\n\n\n");
			printf("	������ �÷��̾�(You)�� �����մϴ�.\n");
			printf("	ī�� ������ ���� 21�� ����� ���� �¸��մϴ�.\n");
			printf("	J, Q, K�� 10���� ����մϴ�.\n");
			printf("	A�� ��Ȳ�� ���� 1Ȥ�� 11�� ����մϴ�. (���α׷��� ��Ȳ�� ���߾� ������ ������ ����մϴ�.)\n");
			printf("	ī�� ������ ���� 21�� �ʰ��ϰ� �Ǹ�(BUST) �й��մϴ�.\n");
			printf("\n\n");
			printf("					���� ����\n\n");
			printf("	0. �ݾ��� �����մϴ�.\n");
			printf("	1. 2���� ī�带 �����޽��ϴ�.\n");
			printf("	   �̶� ������ ī��� 1�常 �����˴ϴ�.\n");
			printf("	2. ī�带 �� ������(HIT), �׸� ������(STAY) �����մϴ�.\n");
			printf("	   ī��� BUST(21 �ʰ�) �� �� ���� ���� �� �ֽ��ϴ�.\n");
			printf("	3. ���� ó��(ī�� 2���� ���� ����)�� ���Ͽ� ������ ����(SURRENDER)�� �� �ֽ��ϴ�.\n");
			printf("	   ���ñݾ��� 0.5�踦 �ް� ������ ����˴ϴ�. \n");
			printf("	4. �׺����� �������, 2�� ������ �ݺ���\n");
			printf("	   ī�带 �� �̻� ���� �ʴ´ٴ� ����(STAY)�� �ϸ�, ������ ������ �˴ϴ�.\n");
			printf("	5. ������ ������ ��Ģ�� ���� ī�带 �޽��ϴ�.(16���ϸ� HIT, 17�̻��̸� STAY)\n");
			printf("	6. ������ ���ʰ� ������, ī�� ������ ������ ���и� �����մϴ�.\n");
			printf("	   (21�� ����� ���� �¸�, 21�ʰ��� �й�)\n");
			printf("	7. �¸��� ���ñݾ��� 2��, ���ºν� ���ñݾ��� 1�踦 �ް�, �й�� ���ñݾ��� �ҽ��ϴ�.\n");
			printf("	8. 1�� ��Ȳ����, ī�� ������ ���� 21�� �Ǹ�(BLACK JACK) ���� �ݾ��� 2.5�踦 �޽��ϴ�.\n");
			printf("	   ��, �������� 21�Ͻ�, ���ºΰ� �˴ϴ�.\n");
			break;
		case(2):
			clear(50);
			printf("					 ��ī��\n\n\n");
			printf("	������ �÷��̾ �����մϴ�.\n");
			printf("	1. ������ �¸�, 2. �÷��̾��� �¸�, 3. ���º�(TIE), 4.���� ù ī�� �������� ����(PAIR)\n");
			printf("	4���� ����� �ϳ��� ������ �� �ֽ��ϴ�.\n");
			printf("	ī�� �������� 1���ڸ��� ū���� �¸��մϴ�.\n");
			printf("	10, J, Q, K�� 0���� ����մϴ�.\n");

			printf("\n\n");
			printf("					���� ����\n\n");
			printf("	0. ����, �÷��̾�, TIE(���º�), PAIR(ùī�� ���º�)��,\n");
			printf("	   �ϳ��� �����Ͽ� �����մϴ�.\n");
			printf("	1. ���� 2���� ī�带 �����޽��ϴ�.\n");
			printf("	2. ���� ī���� ���� ������, PAIR�� �����Ѱ��,\n");
			printf("	   �¸��Ͽ� ������ �޽��ϴ�. (3~6�� �������� �ʽ��ϴ�.)\n");
			printf("	3. ����, �÷��̾��� ��� �����̶� ���ڰ� 8,9���(Netural),\n");
			printf("	   ī�带 �߰��� ���� �ʰ�, �ºθ� �����մϴ�. (3~5�� �������� �ʽ��ϴ�.)\n");
			printf("	4. Netural�� �ƴѰ��, �켱 �÷��̾� ����, ���� ī���� �����տ� ����,\n");
			printf("	   ī�带 �� �ްų�, ���� �ʽ��ϴ�.\n");
			printf("	5. ������ ������ ���� �÷��̾ �߰��� ���� ī���� ���� �����տ� ����,\n");
			printf("	   ī�带 �� �ްų�, �����ʽ��ϴ�.\n");
			printf("	6. �÷��̾�� ������ ī�� �߰��� ������, �ºθ� �����մϴ�.\n");
			printf("	   �������� 1�� �ڸ��� ū ���� �¸��մϴ�.\n");
			printf("	7. �ºθ� ���� ��� 1��, TIE�� ������ 8��,\n");
			printf("	   PAIR�� ������ 11���� ����� �޽��ϴ�.\n");
			break;
		case(3):
			clear(50);
			printf("����ī�� ��Ŀ\n");
			printf("�̱���\n");
			break;

		case(4):
			clear(50);
			printf("					 ��  ��\n\n\n");
			printf("	������ ���� ����ϸ� �¸��մϴ�.\n");
			printf("	�� ���� �� 0.1�� ���� 0~9�� �Ÿ��� �������� �̵��մϴ�. \n");
			printf("	���� ���� GOAL�� �����ϴ� ���� ����ϸ�, ���� ����� �����մϴ�.\n");
			printf("	������ ���� ���� ����� ���, �������� �����մϴ�.\n");

			printf("\n\n");
			printf("					���� ����\n\n");
			printf("	0. 1~4�� �� ��, 1������ ���� �����մϴ�.\n");
			printf("	1. ������ �ϸ�, �渶�� �����մϴ�.\n");
			printf("	2. ���߽� ���ñݾ��� 2�踦 ������,�����߽� ���ñݾ��� �ҽ��ϴ�. \n");
			break;
		}

		int a;
		printf("\n");
		printf("�ٸ� ���� ���� ��� : 1                 ���� �����ϱ� : 2      \n");
		scanf("%d", &a);
		getchar();
		while (1) {
			if (a == 1) {
				break;
			}
			else if (a == 2) {
				return;
			}
			else {
				printf("1�� 2�߿����� ����ּ���\n");
				printf("�ٸ� ���� ���� ��� : 1                 ���� �����ϱ� : 2      \n");
				scanf("%d", &a);
				getchar();
			}
		}

	}

}

void print_main() {
	int color = 0;
	srand(time(NULL));
	while (1) {


		clear(36);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
		printf("                   /$$$$$$     /$$$$$$     /$$$$$$   /$$$$$$  /$$   /$$   /$$$$$$\n");
		printf("                  / $$__ $$   / $$__ $$   / $$_  $$ |_  $$_/ | $$$ | $$  /$$__  $$\n");
		printf("                  | $$  \\_/  | $$   \\$$  | $$  \\__/   | $$   | $$$$| $$ | $$  \\ $$\n");
		printf("                  | $$       | $$$$$$$$  | $$$$$$     | $$   | $$ $$ $$ | $$  | $$\n");
		printf("                  | $$       | $$__  $$   \\____  $$   | $$   | $$  $$$$ | $$  | $$\n");
		printf("                  | $$   $$  | $$  | $$   /$$  \\ $$   | $$   | $$\\  $$$ | $$  | $$\n");
		printf("                  | $$$$$$/  | $$  | $$  |  $$$$$$/  /$$$$$$ | $$ \\  $$ | $$$$$$ /\n");
		printf("                  \\/_____/   |__/  |__/   \\______/  |______/ |__/  \\__/ \\_______/\n");
		clear(11);

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		printf("                                   �ƹ�Ű�� �Է��ϸ� �����մϴ�.");
		clear(5);
		if (kbhit()) {
			getch();
			break;
		}

		Sleep(1000);

		color = rand() % 16;
	}
}
int main() {
	system("mode con cols=100 lines=35");
	print_main();
	int money1 = 1000;
	push = 0;
	best = 0;
	int g = select_game();
	start_game(g, &money1);
}