#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 2048

//メソッドの宣言
static void do_cat(const char *path);
static void die(const char *s);


int main(int argc, char *argv[]) {
	//変数の宣言
    int i;

	//引数がひとつもない場合
    if (argc < 2) {
		//エラー
        fprintf(stderr, "%s: file name not given\n", argv[0]);
        exit(1);
    }
    for (i = 1; i < argc; i++) {
        do_cat(argv[i]);
    }
	//正常終了
    exit(0);
}

/**
 * 
 **/
static void do_cat(const char *path) {

	//変数の宣言
    int fd;
    unsigned char buf[BUFFER_SIZE];
    int n;

	//ファイルを読み込み専用で開く
    fd = open(path, O_RDONLY);
	//エラーならdie()を呼び出す
    if (fd < 0) die(path);
	//無限ループ
    for (;;) {
		//fdのファイルをbufにbufのサイズ文読み込む
        n = read(fd, buf, sizeof buf);
		//エラーならdie()を呼び出す
        if (n < 0) die(path);
		//ファイルの最後まで読み込んだ場合
        if (n == 0) break;
		//bufのデータをn文だけ標準出力に書き出す
        if (write(STDOUT_FILENO, buf, n) < 0) die(path);
    }
	//ファイルを閉じる
	//エラーならdie()を呼び出す
    if (close(fd) < 0) die(path);
}

/**
 * エラーが発生した場合にプログラムを終了させるメソッド
 **/
static void die(const char *s) {
	//errnoの値に合わせたエラーメッセージを標準エラー出力に出力
    perror(s);
    exit(1);
}
