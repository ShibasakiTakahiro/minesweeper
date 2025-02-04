//マインスイーパの課題(version.1)
#include<stdio.h>
#include<stdlib.h> //rand関数を使用するために必要
#include<time.h> //time関数をしようするために必要

#define MS_SIZE 8 //ゲームボードのサイズ

int main(void){
    int mode; //モードを保持(モード：セルを開く,フラグを立てる/除去する)
    int number_of_mines = 10; //地雷数のデフォルト値は10
    int mine_map[MS_SIZE][MS_SIZE]; //地雷セルと数字セルを記録
    int game_board[MS_SIZE][MS_SIZE]; //ゲームの進行を記録するためもゲームボード
    int count=0; //地雷を置くのに使う
    int x,y; //地雷の座標設定
    int count1=0; //周囲８近傍の地雷を数えるために使用  
    int count2;//課題５でgame_boardの0の数を数えるのに使用
    int i,j;
    srand((unsigned)time(NULL)); //time関数で現在時刻を取得し、乱数を初期化する
    
//課題１　地雷をランダムにセット
//---マップとボードの初期化--------------
for(i=0;i<MS_SIZE;i++){
    for(j=0;j<MS_SIZE;j++){
        mine_map[j][i]=0;
    }
}
for(i=0;i<MS_SIZE;i++){
            for(j=0;j<MS_SIZE;j++){
                game_board[j][i]=0;
            }
        }
//---------------------------------------

//---爆弾のセット-----------------------
do{
    x= rand()%8;
    y= rand()%8;
    if(mine_map[y][x]==0){
       mine_map[y][x]=-1;
        count++;
    }
}while(count<number_of_mines);
//-------------------------------------

//---周囲８近傍の爆弾の個数をカウント--
for(x=0; x<MS_SIZE; x++){
    for(y=0; y<MS_SIZE; y++){
        count1=0;
        for(i=-1;i<=1;i++){
            for(j=-1;j<=1;j++){
	      if(x+i<0 || y+j<0 || x+i>=MS_SIZE || y+j>=MS_SIZE){//カウントしない条件
                }
                else{
                    if(mine_map[y+j][x+i]==-1){
                        count1++;
                    }
                }
            }
     
        }
        if(mine_map[y][x]==-1){//爆弾を選んだ場合
            count1--;
        }
	else{
        mine_map[y][x]=count1;
	}
    } 
}
//------------------------------------

//---ゲームボードを表示する---------
printf("[y]\n\n");
for(i=0;i<MS_SIZE;i++){
    printf("%d|",i);
    for(j=0;j<MS_SIZE;j++){
      if(game_board[i][j]==0){
	  printf("%3c",'x');
        }
    }
     printf("\n");
}
printf("  ");
for(i=0;i<MS_SIZE;i++){
    printf("----");
}
printf("\n");
printf("  ");
for(i=0;i<MS_SIZE;i++){
    printf("%3d",i);
}
printf(" [x]\n");
//--------------------------------------------

    //課題２　各セルの８近傍の地雷をカウント

while(count2!=10){ //課題５ ゲームの終了条件を決め、終了条件を満たすまでループを継続

    printf("モードを選択してください：セルを開く（１）,フラグを設置/除去する（２）:");
    scanf("%d",&mode);
    while(mode!=1 && mode!=2){
        printf("１か２を入力してください");
        scanf("%d",&mode);
    }

    //ここでユーザーがセルを設定
    printf("セルを指定してください\n");
    printf("x=");
    scanf("%d",&x);
    printf("y=");
    scanf("%d",&y);
    if(mode==1){
        /*
        課題３ セルを開ける. 地雷があればゲームオーバー.
        地雷がなければ選択したセルと周囲８近傍のセルを開ける.
        */
        
        if(mine_map[y][x]==-1){
            printf("ゲームオーバー\n");
	    exit(0);//強制的に終了
        }
        else{
            for(i=-1; i<=1; i++){
                for(j=-1; j<=1; j++){
                    if(x+i<0 || y+j<0 || x+i>=MS_SIZE || y+j>=MS_SIZE){
                    }
                    else{
                        if(mine_map[y+j][x+i]!=-1){
                            game_board[y+j][x+i]=1;
                        }
                    }
                }
                
            }
            
//---ゲームボードの表示---------------------
            printf("[y]\n\n");
            for(i=0;i<MS_SIZE;i++){
                printf("%d|",i);
                for(j=0;j<MS_SIZE;j++){
                    if(game_board[i][j]==0){
		      printf("%3c",'x');
                    }
                    if(mine_map[i][j]==0 &&game_board[i][j]==1){
                        printf("   ");
                    }
                    if(mine_map[i][j]!=0 &&game_board[i][j]==1){
                        printf("%3d",mine_map[i][j]);
                    }
                    if(game_board[i][j]==2){
		      printf("%3c",'o');
                    }
                }
                printf("\n");
            }
            printf("  ");
            for(i=0;i<MS_SIZE;i++){
                printf("----");
            }
            printf("\n");
            printf("  ");
            for(i=0;i<MS_SIZE;i++){
                printf("%3d",i);
            }
            printf(" [x]\n");
//----------------------------------------------
        }
    }

    else{
            /*
            課題４ 選択されたセルにフラグを設置する
            */
        //ここでユーザーがフラグを設定
	game_board[y][x]=2;
    }
    
    count2=0;
    for(x=0;x<MS_SIZE; x++){
        for(y=0;y<MS_SIZE; y++){
            if(game_board[y][x]==0){ 
            count2++;
            }
        }
    }
        if(count2==10){//課題５ ゲームクリアの条件 0の数をカウントしていく
            printf("Congraturation!\n");
        }
}
        return 0;
}
