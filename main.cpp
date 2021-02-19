/************************************************************
■【C言語】Linuxでのkbhit関数（キーイベントの取得）
	https://hotnews8.net/programming/tricky-code/c-code03
	
■Unixにリアルタイムキー処理をプログラミングする。（C言語　kbhit） 
	http://i2blog.matrix.jp/index.php?UID=1479357418
************************************************************/
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>


/************************************************************
************************************************************/

/******************************
******************************/
int kbhit(void)
{
	struct termios oldt, newt;
	int ch;
	int oldf;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
	fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

	ch = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	fcntl(STDIN_FILENO, F_SETFL, oldf);

	if (ch != EOF) {
		ungetc(ch, stdin);
		return 1;
	}

	return 0;
}

/******************************
******************************/
int main(void)
{
	printf("please input any key > ");

	while (1) {
		if (kbhit()) {
			printf("\n");
			printf("the key was : %c\n", getchar());
			break;
		}
		
		// sleep(1); // sec
		usleep(10 * 1000);
	}

	return 0;
}
