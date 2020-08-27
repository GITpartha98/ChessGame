#include<iostream>

#include<iomanip>

#include<algorithm>

#include<vector>

#include<fstream>

#include<queue>


#include<string.h>

#include<string>

#include<sstream>

#define ERR_MSG std::cout<<"INVALID "

#define K_RULES {{0,1},{1,0},{1,1},{-1,0},{0,-1},{-1,-1},{-1,1},{1,-1}};

#define N_RULES {{1,2},{2,1},{-1,-2},{-2,-1},{-1,2},{-2,1},{1,-2},{2,-1}};

#define W_PIECES {"WR","WN","WB","WQ","WK","WB","WN","WR"}

#define B_PIECES {"BR","BN","BB","BQ","BK","BB","BN","BR" };

#define AllWhite {'W','W','W','W','W','W','W','W'}

#define AllBlack {'B','B','B','B','B','B','B','B'}

class Position
{
   public:
    int row;
    int col;
    std::string notation;

    Position(std::string Not)
    {
          col=(Not[0]-'a'+1);
          row=(9-(Not[1]-'0'));
         notation=Not;
    }

    Position(int R,int C)
    {
         row=R;
         col=C;
         notation+=(col+'a'-1);
         notation+=(row-9)+'0';
    }

};
class pieces
{
    public:
    char color;
    Position curr_pos,prev_pos;
    int cap_flag;

    pieces(char X):curr_pos{-1,-1},prev_pos{-1,-1}
    {
        color=X; //validate for B/W
        cap_flag=0;
    }

    void MK_MV(int row,int col)
    {
        /*for(int i=0;i<2;i++)
        {
            prev_pos[i]=curr_pos[i];
        }*/
        prev_pos=curr_pos;
       // std::cout<<"PREVIOUS POSITION UPDATED \n";

        curr_pos.row=row;
        curr_pos.col=col;

       // std::cout<<"CURRENT POSITION UPDATED "<<curr_pos.row<<" "<<curr_pos.col<<"\n";
    }

    void display()
    {
        std::cout<<"COLOR:"<<color<<std::endl;
        for(int i=0;i<2;i++)
        {
            std::cout<<" current pos "<<curr_pos.row<<" prev pos "<<prev_pos.col<<std::endl;
        }
    }
};
class pawn:public pieces
{
    char name='P';
public:
    pawn(char X):pieces(X)
    {

    }
    void P_display()
    {
        std::cout<<"type"<<name<<std::endl;
        display();
    }

};

class king:public pieces
{
    char name='K';

public:
    int castle_flag=0;

    king(char X):pieces(X)
    {

    }
};

class knight:public pieces
{
    char name='N';

    public:
        knight(char X):pieces(X)
        {

        }
};

class bishop:public pieces
{
    char name='B';

public:
    bishop (char X):pieces(X)
    {

    }
};

class rook:public pieces
{
    char name='R';
public:
    int castle_flag=0;
    rook(char X):pieces(X)
    {

    }

};
class queen:public pieces
{
    char name='Q';
public:
    queen(char X):pieces(X)
    {

    }
};
class chessboard
{
   std::string C_BRD[9][9];

   std::queue<Position> NotationRecord;

   //
   pawn WP[8],BP[8];
   king WK,BK;
   knight WN[2],BN[2];
   bishop WB[2],BB[2];
   rook WR[2],BR[2];
   queen WQ,BQ;

   //PROMOTED PIECES//
   knight WNP[8];
   bishop WBP[8];
   rook   WRP[8];
   queen  WQP[8];

   //
   knight BNP[8];
   bishop BBP[8];
   rook   BRP[8];
   queen  BQP[8];




public:
  chessboard():WP AllWhite,BP AllBlack ,WK('W'),BK('B'),WN{'W','W'},BN{'B','B'},WB{'W','W'},BB{'B','B'},WR{'W','W'},BR{'B','B'},WQ('W'),BQ('B'),WQP AllWhite,WRP AllWhite,WBP AllWhite,WNP AllWhite,BQP AllBlack,BRP AllBlack,BBP AllBlack,BNP AllBlack

  {
      //std::cout<<"CHESSBOARD CTR ENTERED \n\n";
    for(int R=0;R<9;R++)
        for(int C=0;C<9;C++)
    {
        C_BRD[R][C]="XX";
    }

     // std::cout<<"CHESSBOARD CREATED \n\n";
      for(int i=1;i<9;i++)
    {
       // std::cout<<"INIT LOOP ENTERED \n\n";
        std::stringstream ss;
       ss<<i;
       std::string s;
        ss>>s;
        C_BRD[0][i]='a'+i-1;
        C_BRD[i][0]='9'-i;
        C_BRD[2][i]="BP"+s;
        C_BRD[7][i]="WP"+s;
        BP[i-1].MK_MV(1,i);
        WP[i-1].MK_MV(7,i);

    }
    //DISPLAY KINGS POSITIONS
    C_BRD[1][5]="BK";
    C_BRD[8][5]="WK";
    WK.MK_MV(8,5);
    BK.MK_MV(1,5);

    //DISPLAY KNIGHTS POSITIONS
    C_BRD[1][2]="BN1";
    C_BRD[1][7]="BN2";
    C_BRD[8][2]="WN1";
    C_BRD[8][7]="WN2";
    BN[0].MK_MV(1,2);
    BN[1].MK_MV(1,7);
    WN[0].MK_MV(8,2);
    WN[1].MK_MV(8,7);

    //DISPLAY BISHOPS POSITION
    C_BRD[1][3]="BB1";
    C_BRD[1][6]="BB2";
    C_BRD[8][3]="WB1";
    C_BRD[8][6]="WB2";
    BB[0].MK_MV(1,3);
    BB[1].MK_MV(1,6);
    WB[0].MK_MV(8,3);
    WB[1].MK_MV(8,7);

    //DISPLAY ROOKS POSITIONS
    C_BRD[1][1]="BR1";
    C_BRD[1][8]="BR2";
    C_BRD[8][1]="WR1";
    C_BRD[8][8]="WR2";
    BR[0].MK_MV(1,1);
    BR[1].MK_MV(1,8);
    WR[0].MK_MV(8,1);
    WR[1].MK_MV(8,8);

    //DISPLAY QUEEN POSITION
    C_BRD[1][4]="BQ";
    C_BRD[8][4]="WQ";
    BQ.MK_MV(1,4);
    WQ.MK_MV(8,4);

  }

    void display()
    {
        std::cout<<"\n\n CHESSBOARD DISPLAY  \n\n";

     for(int R=0;R<9;R++)
     {

        for(int C=0;C<9;C++)
        {
           std::cout<<std::setw(5)<<C_BRD[R][C]<<"  ";
        }
     std::cout<<"\n\n";
     }

  }

bool make_move(std::string Move,char turn,char Mode)
  {
      std::string notation;
      notation.assign(Move,0,2);
      Position Initial(notation);

      NotationRecord.push(Initial);
     // int col=notation[0]-'a'+1;
     // int row=9-(notation[1]-'0');

      //std::cout<<Initial.row<<" "<<Initial.col<<"\n\n";

        std::string PieceType=FIND_PIECE(Initial.row,Initial.col);

     if(PieceType[0]!= turn)
     {
        NotationRecord.pop();
       std::cout<<"\n\n\b INVALID POSTION PIECE DOES NOT EXIST IN THAT POSITION "<<std::endl;
         return 0;
      }//FIND_PIECE(row,col)!="XX"&&FIND_PIECE(row,col)!="NN")


        // std::cout<<FIND_PIECE(row,col)<<std::endl;
        //std::string PieceType=FIND_PIECE(row,col);

        std::string PIECE_NAME;
        PIECE_NAME.assign(PieceType,0,2);

        std::vector<std::string> final_pos=LEGALMOVES(PIECE_NAME,Initial.row,Initial.col,1);

        chessboard temp=*this;//ERROR EITHER IN LEGAL MOVES/ ERROR EITHER HERE

        std::vector<std::string> FinalLegal=FilterMoves(final_pos,Initial);//get_leagal_mpve()

        *this=temp;
      if(FinalLegal.size()==0)
      {
          NotationRecord.pop();
          std::cout<<"\n\n\b NO LEGAL MOVES POSSIBLE,CHOOSE A DIFFERENT PIECE ";
          return 0;
      }
      std::cout<<"POSSIBLE MOVES OF "<<PieceType<<" ARE ";
       for(int c1=0;c1<FinalLegal.size();c1++)
       {
           std::cout<<FinalLegal[c1]<<"  ";
       }

       std::string MOVE;

       if(Mode=='U')
       {

       std::cout<<"\n\n"<<"SELECT ONE LEGAL MOVE: ";



       std::cin>>MOVE;
       }

       else if(Mode=='R')
       {
         MOVE.assign(Move,2,2);
           if(MOVE=="KC")
           {
               MOVE="0-0";
           }
           else if(MOVE=="QC")
           {
               MOVE="0-0-0";
           }
       }

       int flag=0;

       for(int c1=0;c1<FinalLegal.size();c1++)
       {
           if(MOVE==FinalLegal[c1])
           {
               flag=1;


           }
       }

       if(!flag)
       {
           NotationRecord.pop();
           std::cout<<"\n\n\b MOVE CHOSEN NOT A LEGAL MOVE ";
           return 0;
       }

int N_COL,N_ROW;
chessboard C2=*this;
//std::cout<<"\n"<<MOVE<<"\n";


if(MOVE=="0-0"||MOVE=="0-0-0"){
       // std::cout<<"\n\n I am making a castle move ";

         //UPDATE POSITION IF CASTLES//
         switch(PieceType[0])
         {
         case 'W':
            if(MOVE=="0-0-0")
            {
                NotationRecord.push(Position("0-0-0"));
                C_BRD[8][1]="XX";
                C_BRD[8][5]="XX";
                C_BRD[8][4]="WR1";
                C_BRD[8][3]="WK";

                WK.MK_MV(8,3);
                WR[0].MK_MV(8,4);

            }

            else{
                    NotationRecord.push(Position("0-0"));
                C_BRD[8][8]="XX";
                C_BRD[8][5]="XX";
                C_BRD[8][7]="WK";
                C_BRD[8][6]="WR2";

                WK.MK_MV(7,7);
                WR[1].MK_MV(7,6);
            }
            break;
            case'B':
               if(MOVE=="0-0-0")
            {
                NotationRecord.push(Position("0-0-0"));
                C_BRD[1][1]="XX";
                C_BRD[1][5]="XX";
                C_BRD[1][4]="BR1";
                C_BRD[1][3]="BK";

                BK.MK_MV(1,3);
                BR[0].MK_MV(1,4);

            }

            else{
                    NotationRecord.push(Position("0-0"));
                C_BRD[1][8]="XX";
                C_BRD[1][5]="XX";
                C_BRD[1][7]="BK";
                C_BRD[1][6]="BR2";

                BK.MK_MV(1,7);
                BR[1].MK_MV(1,6);
            }
         }
}

else
{
   // std::cout<<"\n I am making a Non-Castling Move \n";
    Position Final(MOVE);

NotationRecord.push(Final);
      // std::cout<<"\n\n"<<Final.row<<" "<<Final.col;

        //chessboard C2=*this;

         C_BRD[Initial.row][Initial.col]="XX"; //set empty to cur_row,cur_col

         C_BRD[Final.row][Final.col]=PieceType;

         UPDATE_POS(PieceType,Final,MOVE);
}



         if(CHK_IF_CHECK(PieceType[0]))
         {
             std::cout<<"\n\n\b"<<"ILLEGAL BECAUSE KING IS UNDER CHECK ";

             //C_BRD[N_ROW][N_COL]="XX";

             //C_BRD[row][col]=PieceType;
             *this=C2;

             UPDATE_POS(PieceType,Initial,MOVE);

             NotationRecord.pop();
             NotationRecord.pop();

             return 0;
         }

    UpdateCastleFlag();

    for(int i=1;i<9;i++)
    {
        std::string temp;
        temp.assign((FIND_PIECE(1,i)),0,2);
        if(temp=="WP")
        {
            Position PromSqr(1,i);
            PawnPromotion('W',PromSqr);

        }

        temp.assign(FIND_PIECE(8,i),0,2);
        if(temp=="BP")
        {
            Position PromSqr(8,i);
            PawnPromotion('B',PromSqr);
        }
    }
chessboard temp2=*this;



    if (CheckIfCheckmate(PieceType[0]))
    {
        *this=temp2;
        return 0;
    }

    *this=temp2;

       return 1;




     }














  std::string FIND_PIECE(int row ,int col)
  {
     if(CHK_BOUNDARY(row,col))
     {

         //std::cout<<C_BRD[row][col]<<std::endl;
         return C_BRD[row][col];
     }
     else return "NN";
  }

  bool CHK_BOUNDARY(int R,int C)
  {
      return R>=1&&C>=1&&R<9&&C<9;
  }

  std::vector<std::string> LEGALMOVES(std::string piece_name,int ROW_IN,int COL_IN,int CastleFlag)
  {
      std::vector <std::string> legals;

      if(piece_name=="WP")
        {
            std::string C1=FIND_PIECE(ROW_IN-1,COL_IN-1);
            std::string C2=FIND_PIECE(ROW_IN-1,COL_IN+1);
            if(FIND_PIECE(ROW_IN-1,COL_IN)=="XX")
                    {
                        legals.push_back(NOTATION(ROW_IN-1,COL_IN));
                       // C_BRD[ROW_IN-1][COL_IN]=piece_name;
                       if(ROW_IN==7)
                        {

                            if(FIND_PIECE(ROW_IN-2,COL_IN)=="XX")
                            {
                                //C_BRD[ROW_IN+2][COL_IN]=piece_name;
                                legals.push_back(NOTATION(ROW_IN-2,COL_IN));
                            }
                        }

                    }
            if(C1[0]=='B')
            {
                legals.push_back(NOTATION(ROW_IN-1,COL_IN-1));
            }
             if(C2[0]=='B')
            {
                legals.push_back(NOTATION(ROW_IN-1,COL_IN+1));
            }
        }

       else if(piece_name=="BP")
          {
            std::string C1=FIND_PIECE(ROW_IN+1,COL_IN-1);
            std::string C2=FIND_PIECE(ROW_IN+1,COL_IN+1);

           if(FIND_PIECE(ROW_IN+1,COL_IN)=="XX")
                    {
                        legals.push_back(NOTATION(ROW_IN+1,COL_IN));
                       // C_BRD[ROW_IN-1][COL_IN]=piece_name;
                       if(ROW_IN==2)
                        {

                            if(FIND_PIECE(ROW_IN+2,COL_IN)=="XX")
                            {
                                //C_BRD[ROW_IN+2][COL_IN]=piece_name;
                                legals.push_back(NOTATION(ROW_IN+2,COL_IN));
                            }
                        }

                    }
                    if(C1[0]=='W')
            {
                legals.push_back(NOTATION(ROW_IN+1,COL_IN-1));
            }
             if(C2[0]=='W')
            {
                legals.push_back(NOTATION(ROW_IN+1,COL_IN+1));
            }
          }

               //C_BRD[ROW_IN][COL_IN]='X';
               //break;
        switch(piece_name[1])
        {
            case 'K':
                {
                    int RULES[][2]=K_RULES;

                for(int R=0; R<8; R++)
                {
                    std::string temp=FIND_PIECE((ROW_IN+RULES[R][0]),(COL_IN+RULES[R][1]));
                    if(temp[0]!=piece_name[0]&&temp!="NN")
                    {
                        legals.push_back(NOTATION((ROW_IN+RULES[R][0]),(COL_IN+RULES[R][1])));
                        //std::cout<<"\n"<<"King Moves are"<<legals.back() <<"\n";

                    }
                }
            // CASTLING//
            if(CastleFlag)
            {
                 switch(piece_name[0])
                        {
                            /*RULES TO CHECK
                            KING SHOULD NOT BE UNDER CHECK
                            F1,G1 SQUARES SHOULD NOT BE UNDER CHECK
                            D1 C1 SQUARES SHOULD NOT BE UNDER CHECK
                            KING SHOULD NOT HAVE MOVE
                            CORRESSPONDING ROOKS MUST NOT HAVE MOVED*/
                        case 'W':
                            if(WK.castle_flag==0)
                            {
                                if(WR[0].castle_flag==0&&FIND_PIECE(ROW_IN,COL_IN-1)=="XX"&&FIND_PIECE(ROW_IN,COL_IN-2)=="XX"&&FIND_PIECE(ROW_IN,COL_IN-3)=="XX")
                                {
                                    if(!CHK_IF_CHECK('W')&&!CHK_IF_CHECK('W',ROW_IN,COL_IN-1)&&!CHK_IF_CHECK('W',ROW_IN,COL_IN-2))
                                    legals.push_back("0-0-0");
                                }
                                if(WR[1].castle_flag==0&&FIND_PIECE(ROW_IN,COL_IN+1)=="XX"&&FIND_PIECE(ROW_IN,COL_IN+2)=="XX")
                                {
                                    //if(!CHK_IF_CHECK('W')&&!CHK_IF_CHECK('W',ROW_IN,COL_IN+1))
                                    if((!CHK_IF_CHECK('W'))&&!CHK_IF_CHECK('W',ROW_IN,COL_IN+1)&&!CHK_IF_CHECK('W',ROW_IN,COL_IN+2))
                                    legals.push_back("0-0");
                                }
                            }

                              case 'B':
                            if(BK.castle_flag==0)
                            {
                                if(BR[0].castle_flag==0&&FIND_PIECE(ROW_IN,COL_IN-1)=="XX"&&FIND_PIECE(ROW_IN,COL_IN-2)=="XX"&&FIND_PIECE(ROW_IN,COL_IN-3)=="XX")
                                {
                                    if(!CHK_IF_CHECK('B')&&!CHK_IF_CHECK('B',ROW_IN,COL_IN-1)&&!CHK_IF_CHECK('B',ROW_IN,COL_IN-2))
                                    legals.push_back("0-0-0");
                                }
                                if(BR[1].castle_flag==0&&FIND_PIECE(ROW_IN,COL_IN+1)=="XX"&&FIND_PIECE(ROW_IN,COL_IN+2)=="XX")
                                {
                                    if(!CHK_IF_CHECK('B')&&!CHK_IF_CHECK('B',ROW_IN,COL_IN+1)&&!CHK_IF_CHECK('B',ROW_IN,COL_IN+2))
                                    legals.push_back("0-0");
                                }
                            }
                        }
            }
                break;
            }

            case 'N':
                {
                    int RULES[][2]=N_RULES;
                  for(int R=0; R<8; R++)
                {
                    std::string temp=FIND_PIECE((ROW_IN+RULES[R][0]),(COL_IN+RULES[R][1]));
                    if(temp[0]!=piece_name[0]&&temp!="NN")
                    {
                        legals.push_back(NOTATION((ROW_IN+RULES[R][0]),(COL_IN+RULES[R][1])));

                    }
                }

                break;
                }

            case 'B':
                    legals=getBishMoves(piece_name,ROW_IN,COL_IN);
                    break;

            case 'R':legals=getRookMoves(piece_name,ROW_IN,COL_IN);
                     break;
            case 'Q':
                legals=getBishMoves(piece_name,ROW_IN,COL_IN);
                auto legals2=getRookMoves(piece_name,ROW_IN,COL_IN);
                legals.insert(legals.end(),legals2.begin(),legals2.end());
                break;
        }
        return legals;
  }


  std::string NOTATION(int row,int col)
  {
      std::string temp;

      temp+=('a'+col-1);
      temp+= (9-row)+'0';

      return temp;
  }

  void UPDATE_POS(std::string PieceType,Position finalpos,std::string SpMove)
 {
     std::string PIECE_type;
     PIECE_type.assign(PieceType,0,2);
    if(PIECE_type=="WP")
       {
                 WP[PieceType[2]-1-'0'].curr_pos=finalpos;
                 //std::cout<<"POSITION UPDATED \n";
       }
    else if(PIECE_type=="BP")
       {
                 BP[PieceType[2]-1-'0'].curr_pos=finalpos;
                 //std::cout<<"POSITION UPDATED \n";
       }
    else if(PIECE_type=="WN")
    {
         if(PieceType[2]=='P')
         {
             WNP[PieceType[3]-1-'0'].curr_pos=finalpos;
             return;
         }
        WN[PieceType[2]-1-'0'].curr_pos=finalpos;
                 //std::cout<<"POSITION UPDATED \n";
    }
    else if(PIECE_type=="BN")
    {

         if(PieceType[2]=='P')
         {
             BNP[PieceType[3]-1-'0'].curr_pos=finalpos;
             return;
         }
          BP[PieceType[2]-1-'0'].curr_pos=finalpos;
                 //std::cout<<"POSITION UPDATED \n";
    }
    else if(PIECE_type=="WK")
    {
        if(SpMove=="0-0")
        {
            WR[1].MK_MV(7,8);
        }
        else{
            WR[0].MK_MV(7,1);
        }
        WK.curr_pos=finalpos;
              //std::cout<<"POSITION UPDATED \n";
    }
    else if(PIECE_type=="BK")
    {
        if(SpMove=="0-0")
        {
            BR[1].MK_MV(1,8);
        }
        else{
            BR[0].MK_MV(1,1);
        }
        BK.curr_pos=finalpos;
        //std::cout<<"POSITION UPDATED \n";
    }
    else if(PIECE_type=="BB")
    {
        if(PieceType[2]=='P')
         {
             BBP[PieceType[3]-1-'0'].curr_pos=finalpos;
             return;
         }
          BB[PieceType[2]-1-'0'].curr_pos=finalpos;
                 //std::cout<<"POSITION UPDATED \n";
    }
    else if(PIECE_type=="WB")
    {
         if(PieceType[2]=='P')
         {
             WBP[PieceType[3]-1-'0'].curr_pos=finalpos;
             return;
         }
          WB[PieceType[2]-1-'0'].curr_pos=finalpos;
                 //std::cout<<"POSITION UPDATED \n";
    }
    else if(PIECE_type=="BR")
    {
        if(PieceType[2]=='P')
         {
             BRP[PieceType[3]-1-'0'].curr_pos=finalpos;
             return;
         }
          BR[PieceType[2]-1-'0'].curr_pos=finalpos;
                 ////std::cout<<"POSITION UPDATED \n";
    }
    else if(PIECE_type=="WR")
    {
        if(PieceType[2]=='P')
         {
             WRP[PieceType[3]-1-'0'].curr_pos=finalpos;
             return;
         }
          WR[PieceType[2]-1-'0'].curr_pos=finalpos;
                 //std::cout<<"POSITION UPDATED \n";
    }
      else if(PIECE_type=="BQ")
    {
          if(PieceType[2]=='P')
         {
             BQP[PieceType[3]-1-'0'].curr_pos=finalpos;
             return;
         }
        BQ.curr_pos=finalpos;
        //std::cout<<"POSITION UPDATED \n";
    }
      else if(PIECE_type=="WQ")
    {
         if(PieceType[2]=='P')
         {
             WQP[PieceType[3]-1-'0'].curr_pos=finalpos;
             return;
         }
        WQ.curr_pos=finalpos;
        //std::cout<<"POSITION UPDATED \n";
    }


       }





bool CHK_IF_CHECK(char color)
{
    //std::cout<<"CHK_IF_CHECK method entered \n";
  for(int i=1;i<9;i++)
    for(int j=1;j<9;j++)
  {
      std::string temp;
      std::string PieceType=FIND_PIECE(i,j);
      if(PieceType!="XX"&&PieceType!="NN"&&PieceType[0]!=color)
         temp.assign(FIND_PIECE(i,j),0,2);
      else continue;
    // std::cout<<" TEMP "<<temp<<"\n\n";

     std::vector<std::string>ALL_MOVES =LEGALMOVES(temp,i,j,0);

     //std::cout<<"LEGAL MOVES ARE ";
     for(int i=0;i<ALL_MOVES.size();i++)
     {
        //std::cout<<ALL_MOVES[i]<<" ";
         if(color=='W')
          {

                  //std::cout<<" "<<ALL_MOVES[i]<<" ";
              if(NOTATION(WK.curr_pos.row,WK.curr_pos.col)==ALL_MOVES[i])
              {
                // std::cout<<"\n\n KING UNDER CHECK";
                return 1;
              }

          }
        else if(color=='B')
        {
            if(NOTATION(BK.curr_pos.row,BK.curr_pos.col)==ALL_MOVES[i])
            {
              //std::cout<<"\n\n KING UNDER CHECK";
             return 1;
            }
        }
     }


  }
  return 0;
}

bool CHK_IF_CHECK(char color,int row,int col)
{
  //std::cout<<"CHK_IF_CHECK method entered \n";
  for(int i=1;i<9;i++)
    for(int j=1;j<9;j++)
  {
      std::string temp;
      std::string PieceType=FIND_PIECE(i,j);
      if(PieceType!="XX"&&PieceType!="NN"&&PieceType[0]!=color)
         temp.assign(FIND_PIECE(i,j),0,2);
      else continue;
     //std::cout<<" TEMP "<<temp<<"\n\n";

     std::vector<std::string>ALL_MOVES =LEGALMOVES(temp,i,j,0);

     //std::cout<<"LEGAL MOVES ARE ";
     for(int i=0;i<ALL_MOVES.size();i++)
     {
        //std::cout<<ALL_MOVES[i]<<" ";
         if(color=='W')
          {

                  //std::cout<<" "<<ALL_MOVES[i]<<" ";
              if(NOTATION(row,col)==ALL_MOVES[i])
              {
                 std::cout<<"\n\n KING UNDER CHECK";
                return 1;
              }

          }
        else if(color=='B')
        {

            if(NOTATION(row,col)==ALL_MOVES[i])
            {
              std::cout<<"\n\n KING UNDER CHECK";
             return 1;
            }
        }
     }


  }
  return 0;
}


std::vector<std::string> getBishMoves(std::string piece_name,int ROW_IN,int COL_IN)
{
    std::vector<std::string> BishLegals;
    {
                    int dir_flags[]= {0,0,0,0};
                for(int relative_pos=1; relative_pos<8; relative_pos++)
                {
                    //SOUTHWEST DIRECTION
                    std::string temp1=FIND_PIECE(ROW_IN+relative_pos,COL_IN+relative_pos);

                    if((temp1=="XX")&&(dir_flags[0]==0))
                    {
                        //std::cout<<ROW_IN+relative_pos<<COL_IN+relative_pos<<std::endl;;
                       BishLegals.push_back (NOTATION(ROW_IN+relative_pos,COL_IN+relative_pos));
                        //std::cout<<C_BRD[ROW_IN+relative_pos][COL_IN+relative_pos];
                    }
                    else
                    {
                        if((temp1[0]!=piece_name[0])&&(temp1!="NN")&&dir_flags[0]==0)
                        {
                            //std::cout<<"\n\n"<<temp1;
                            //std::cout<<"\n\n"<<ROW_IN+relative_pos<<" "<<COL_IN+relative_pos;
                            BishLegals.push_back (NOTATION(ROW_IN+relative_pos,COL_IN+relative_pos));
                        }
                        //std::string temp=FIND_PIECE()
                        dir_flags[0]=1;
                    }
                    //NORTHWEST DIRECTION
                    std::string temp2=FIND_PIECE(ROW_IN-relative_pos,COL_IN+relative_pos);
                    if((temp2=="XX")&&(dir_flags[1]==0))
                    {
                       BishLegals.push_back (NOTATION(ROW_IN-relative_pos,COL_IN+relative_pos));
                    }
                    else
                    {
                        if((temp2[0]!=piece_name[0])&&(temp2!="NN")&&(dir_flags[1]==0))
                        {
                            BishLegals.push_back (NOTATION(ROW_IN-relative_pos,COL_IN+relative_pos));
                        }

                        dir_flags[1]=1;
                    }

                    //NORTHEAST DIRECTION
                    std::string temp3=FIND_PIECE(ROW_IN-relative_pos,COL_IN-relative_pos);
                    if((temp3=="XX")&&(dir_flags[2]==0))
                    {
                        BishLegals.push_back (NOTATION(ROW_IN-relative_pos,COL_IN-relative_pos));
                    }
                    else
                    {
                         if((temp3[0]!=piece_name[0])&&(temp3!="NN")&&dir_flags[2]==0)
                        {
                            BishLegals.push_back (NOTATION(ROW_IN-relative_pos,COL_IN-relative_pos));
                        }


                        dir_flags[2]=1;
                    }

                  //SOUTHEAST DIRECTION//
                   std::string temp4=FIND_PIECE(ROW_IN+relative_pos,COL_IN-relative_pos);
                    if((temp4=="XX")&&(dir_flags[3]==0))
                    {
                        //std::string temp=FIND_PIECE(ROW_IN+relative_pos,COL_IN+relative_pos);

                        BishLegals.push_back (NOTATION(ROW_IN+relative_pos,COL_IN-relative_pos));
                    }
                    else
                    {
                        if((temp4[0]!=piece_name[0])&&(temp4!="NN")&&dir_flags[3]==0)
                        {

                            BishLegals.push_back (NOTATION(ROW_IN+relative_pos,COL_IN-relative_pos));
                        }

                        dir_flags[3]=1;
                    }

                }

            return BishLegals;
                }
}

std::vector<std::string> getRookMoves(std::string piece_name,int ROW_IN,int COL_IN)
{
    std::vector<std::string> RookLegals;


                    int dir_flags[]= {0,0,0,0};
                for(int relative_pos=1; relative_pos<8; relative_pos++)
                {
                    //SOUTH DIRECTION
                    std::string temp1=FIND_PIECE(ROW_IN+relative_pos,COL_IN);

                    if((temp1=="XX")&&(dir_flags[0]==0))
                    {
                        //std::cout<<ROW_IN+relative_pos<<COL_IN+relative_pos<<std::endl;;
                       RookLegals.push_back (NOTATION(ROW_IN+relative_pos,COL_IN));
                        //std::cout<<C_BRD[ROW_IN+relative_pos][COL_IN+relative_pos];
                    }
                    else
                    {
                        if((temp1[0]!=piece_name[0])&&(temp1!="NN")&&dir_flags[0]==0)
                        {
                           // std::cout<<"\n\n"<<temp1;
                           // std::cout<<"\n\n"<<ROW_IN+relative_pos<<" "<<COL_IN;
                           RookLegals.push_back (NOTATION(ROW_IN+relative_pos,COL_IN));
                        }
                        //std::string temp=FIND_PIECE()
                        dir_flags[0]=1;
                    }
                    //NORTH DIRECTION
                    std::string temp2=FIND_PIECE(ROW_IN-relative_pos,COL_IN);
                    if((temp2=="XX")&&(dir_flags[1]==0))
                    {
                       RookLegals.push_back (NOTATION(ROW_IN-relative_pos,COL_IN));
                    }
                    else
                    {
                        if((temp2[0]!=piece_name[0])&&(temp2!="NN")&&(dir_flags[1]==0))
                        {
                            RookLegals.push_back (NOTATION(ROW_IN-relative_pos,COL_IN));
                        }

                        dir_flags[1]=1;
                    }

                    //EAST DIRECTION
                    std::string temp3=FIND_PIECE(ROW_IN,COL_IN-relative_pos);
                    if((temp3=="XX")&&(dir_flags[2]==0))
                    {
                      RookLegals.push_back (NOTATION(ROW_IN,COL_IN-relative_pos));
                    }
                    else
                    {
                         if((temp3[0]!=piece_name[0])&&(temp3!="NN")&&dir_flags[2]==0)
                        {
                          RookLegals.push_back (NOTATION(ROW_IN,COL_IN-relative_pos));
                        }


                        dir_flags[2]=1;
                    }

                  //WEST DIRECTION//
                   std::string temp4=FIND_PIECE(ROW_IN,COL_IN+relative_pos);
                    if((temp4=="XX")&&(dir_flags[3]==0))
                    {
                        //std::string temp=FIND_PIECE(ROW_IN+relative_pos,COL_IN+relative_pos);

                        RookLegals.push_back (NOTATION(ROW_IN,COL_IN+relative_pos));
                    }
                    else
                    {
                        if((temp4[0]!=piece_name[0])&&(temp4!="NN")&&dir_flags[3]==0)
                        {

                            RookLegals.push_back (NOTATION(ROW_IN,COL_IN+relative_pos));
                        }

                        dir_flags[3]=1;
                    }

                }

         return RookLegals;
}

void UpdateCastleFlag()
{
    if(WK.curr_pos.row!=8||WK.curr_pos.col!=5)
    {
      WK.castle_flag=1;
    }
    if(BK.curr_pos.row!=1||BK.curr_pos.col!=5)
    {
        BK.castle_flag=1;
    }
    if(WR[0].curr_pos.row!=8||WR[0].curr_pos.col!=1)
    {
      WR[0].castle_flag=1;
    }
     if(WR[1].curr_pos.row!=8||WR[1].curr_pos.col!=8)
     {
       WR[1].castle_flag=1;
     }
     if(BR[0].curr_pos.row!=1||BR[0].curr_pos.col!=1)
     {

       BR[0].castle_flag=1;
     }
     if(BR[1].curr_pos.row!=1||BR[1].curr_pos.col!=8)
     {

        BR[1].castle_flag=1;
     }
}


std::vector<std::string> FilterMoves(std::vector<std::string> PosMoves,Position Initial)
{
    chessboard Temp=*this;

    std::string PieceName=FIND_PIECE(Initial.row,Initial.col);
    std::vector<std::string> LegalMoves;

    for(int Iterator1=0;Iterator1<PosMoves.size();Iterator1++)
    {
         C_BRD[Initial.row][Initial.col]="XX";

         Position FinalPos(9-(PosMoves[Iterator1][1]-'0'),(PosMoves[Iterator1][0]-'a'+1));
        //  col=(PosMoves[i][0]-'a'+1);
         // row=(9-(Posmoves[i][1]-'0'));
         C_BRD[(9-(PosMoves[Iterator1][1]-'0'))][(PosMoves[Iterator1][0]-'a'+1)]=PieceName;

         UPDATE_POS(PieceName,FinalPos,PosMoves[Iterator1]);
           if(!CHK_IF_CHECK(PieceName[0]))
           {
               LegalMoves.push_back(PosMoves[Iterator1]);

              // std::cout<<"\n"<<LegalMoves.back();
           }
            UPDATE_POS(PieceName,Initial,PosMoves[Iterator1]);

           *this=Temp;
    }
  return LegalMoves;
}



void PawnPromotion(char color,Position PromSqr)
{
    char piece;
    std::cout<<"What Piece would you like to promote to \n Q,R,B,or N";

    std::cin>>piece;

    std::string Color;
            Color.push_back(color);
              //Color[1]='\0';

              std::cout<<color;

    switch(piece)
    {
    case 'Q':
        { if(color=='W')
                WQP[0].curr_pos=PromSqr;
                else
                BQP[0].curr_pos=PromSqr;

            C_BRD[PromSqr.row][PromSqr.col]=Color+"Q"+"P"+"1";
            break;
        }
    case 'R':
        {  if(color=='W')
                WRP[0].curr_pos=PromSqr;
                else
                BRP[0].curr_pos=PromSqr;
             C_BRD[PromSqr.row][PromSqr.col]=Color+"R"+"P"+"1";
             break;
        }
    case 'B':
        {
            if(color=='W')
                WBP[0].curr_pos=PromSqr;
                else
                BBP[0].curr_pos=PromSqr;

              C_BRD[PromSqr.row][PromSqr.col]=Color+"B"+"P"+"1";
             break;
        }
    case 'N':
        {
            if(color=='W')
                WNP[0].curr_pos=PromSqr;
                else
                BNP[0].curr_pos=PromSqr;
              C_BRD[PromSqr.row][PromSqr.col]=Color+"N"+"P"+"1";
             break;
        }

    default: "Invalid PieceType \n";
              PawnPromotion(color,PromSqr);

    }


}

bool CheckIfCheckmate(char color)
{

  switch(color)
    {

    case 'B':
        {
       //std::cout<<"\n Checking if Black gives Checkmate \n";
        //CHK_IF_CHECK('W');std::vector<std::string> AllPieces=FindAllPieces(char color);
      std::vector<std::string> LegalOne;
      std::vector<std::string> Allpieces =FindPiece('W');
      std::vector<Position> AllPosition=FindPositions('W');
      for(int I1=0;I1<Allpieces.size();I1++)
      {
         // chessboard Temp=*this;
         std::vector<std::string> temp =LEGALMOVES(Allpieces[I1],AllPosition[I1].row,AllPosition[I1].col,0);
         std::vector<std::string> Legal=FilterMoves(temp,AllPosition[I1]);
        // *this=Temp;
         LegalOne.insert(LegalOne.end(),Legal.begin(),Legal.end());
      }

         //std::vector<std::string> Legal=FilterMoves(LegalOne);
        if(CHK_IF_CHECK('W')&&LegalOne.size()==0)
        {
            std::cout<<"Congratulations, Black wins by Checkmate \n";
            return 1;
        }
        if(LegalOne.size()==0)
        {
            std::cout<<"\n Oops,Game Drawn by Stalemate \n";
            return 1;
        }
        break;
        }

    case 'W':
        // CHK_IF_CHECK('B');
        {
             std::vector<std::string> LegalOne;
      std::vector<std::string> Allpieces =FindPiece('B');
      std::vector<Position> AllPosition=FindPositions('B');
      for(int I1=0;I1<Allpieces.size();I1++)
      {
         std::vector<std::string> temp =LEGALMOVES(Allpieces[I1],AllPosition[I1].row,AllPosition[I1].col,0);
         std::vector<std::string> Legal=FilterMoves(temp,AllPosition[I1]);
         LegalOne.insert(LegalOne.end(),Legal.begin(),Legal.end());
      }

        if(CHK_IF_CHECK('B')&&LegalOne.size()==0)
        {
            std::cout<<"Congratulations, Black wins by Checkmate \n";
            return 1;
        }
        if(LegalOne.size()==0)
        {
            std::cout<<"\n Oops,Game Drawn by Stalemate \n";
            return 1;
        }
        break;
        }
    }
return 0;
}
std::vector<std::string> FindPiece(char color)
{
    std::vector<std::string> AllPieces;
    for(int i=1;i<9;i++)
    for(int j=1;j<9;j++)
  {

      std::string PieceType=FIND_PIECE(i,j);
      if(PieceType!="XX"&&PieceType!="NN"&&PieceType[0]==color)
         AllPieces.push_back(PieceType);
      else continue;
    // std::cout<<" TEMP "<<temp<<"\n\n";
  }
  return AllPieces;
}

std::vector<Position> FindPositions(char color)
{
    std::vector<Position> AllPos;
    for(int i=1;i<9;i++)
        for(int j=1;j<9;j++)
    {
          std::string PieceType=FIND_PIECE(i,j);
          if(PieceType!="XX"&&PieceType!="NN"&&PieceType[0]==color)
        {
            Position temp("XX");
            temp.row=i;
            temp.col=j;
            AllPos.push_back(temp);
        }
    }
    return AllPos;
}

void PrintNotation()
    {
        int count =0;
        std::cout<<"\n\n GameMoves are: \n";

        auto TempQ=NotationRecord;


        while(!TempQ.empty())
        {
            Position pos1=TempQ.front();
            TempQ.pop();
            Position pos2=TempQ.front();
            TempQ.pop();
            std::cout<<count+1<<"."<< pos1.notation<<" "<<pos2.notation<<std::endl;
            count++;
        }
    }

};




void StartGame(chessboard&);
void ReadGame(chessboard&,std::string Game);
void ReadMe();



int main()
{

   /*std::fstream GameNotation;

   GameNotation.open("C:\\Users\\anbum\\OneDrive\\Desktop\\OOP CODING\\Cpp student exercises\\Projects\\Chessboard project\\All Legal moves\\TestCases\\TestCaseGame1.txt",std::ios::in|std::ios::in|std::ios::app);

    char *FilePtr=new char[1000];
    GameNotation.read(FilePtr,1000);
     std::string Game;
     int i;
     for(i=0;FilePtr[i]!='\0';i++)
     {
         Game+=FilePtr[i];
     }
     Game[i+1]='\0';
     std::cout<<Game<<"\n";
     Game.erase((remove(Game.begin(),Game.end(),'|')),Game.end());
     Game.erase((remove(Game.begin(),Game.end(),'-')),Game.end());
     std::cout<<Game;


    /* for(int i=0;Game[i]!='\0';i+=2)
     {
         std::string Move;
         Move.assign(Game,i,2);
         std::cout<<Move<<"\t";
     }
    /*while(GameNotation)
    {
      GameNotation>>a;
      std::cout<<a;
    }

   //std::cout<<FilePtr[2]<<std::endl;

    GameNotation.close();*/

    ReadMe();

    chessboard C1;

    C1.display();



    std::cout<<"\n\n";

   // ReadGame(C1,Game);



   std::cout<<"\n\nNEW GAME ";

   std::cout<<"\n\nWhite to Move";

   StartGame(C1);

   return 0;
}



void StartGame(chessboard &C1)
{
    int  total_moves=0;
    char turn;

 std::string sqr;

   std::cout<<"\n\nENTER THE SQUARE OF THE PIECE YOU ARE ABOUT TO MOVE ENTER X to EXIT: ";

   std::cin>>sqr;
    while(sqr!="X")
    {
        if(total_moves%2==0)
        {
            turn='W';
            //std::cout<<"WHITE TO MOVE \n";
        }
        else
        {
            turn='B';
            //std::cout<<"BLACK TO MOVE \n";
        }

       if(C1.make_move(sqr,turn,'U'))
       {
           std::cout<<"\n\nMOVE MADE";
            ++total_moves;
       }
        C1.display();

       switch(total_moves%2)
       {
        case 0:std::cout<<"\nWHITE TO MOVE\n";break;
        case 1:std::cout<<"\nBLACK TO MOVE\n";break;
       }
        std::cout<<"\n\nENTER THE SQUARE OF THE PIECE YOU ARE ABOUT TO MOVE ENTER X to EXIT: ";
        std::cin>>sqr;

        if(sqr=="X")
        {
            C1.PrintNotation();

            char choice;
            std::cout<<"\n\n Would you like to Start a NewGame? Y/N";
            std::cin>>choice;
            if(choice=='Y')
            {
                ReadMe();
                chessboard C2;
                StartGame(C2);

            }
        }
    }



    return;
}

void ReadGame(chessboard &C1,std::string Game)
{
   int  total_moves=0;
    char turn;
     for(int i=0;Game[i]!='\0';i+=4)
     {
         std::string Move;
         Move.assign(Game,i,4);
         std::cout<<Move<<"\t";




        if(total_moves%2==0)
        {
            turn='W';
            //std::cout<<"WHITE TO MOVE \n";
        }
        else
        {
            turn='B';
            //std::cout<<"BLACK TO MOVE \n";
        }

       if(C1.make_move(Move,turn,'R'))
       {
           std::cout<<"\n MOVE MADE \n";
            ++total_moves;
       }
       else {
        std::cout<<"Test Case failed \n";
        break;
       }
        C1.display();

       switch(total_moves%2)
       {
        case 0:std::cout<<"\nWHITE TO MOVE\n";break;
        case 1:std::cout<<"\nBLACK TO MOVE\n";break;
       }

       char choice;


       std::cout<<"\nEnter any character to continue Enter X to exit \n";

       std::cin>>choice;

       if(choice=='X')
       {
           std::cout<<"\n Exiting reading the game \n";

           C1.PrintNotation();

           break;
       }

     }
C1.PrintNotation();

     return ;
}

void ReadMe()
{
    std::cout<<"Rules for using the Chat-Based Chessgame \n"<<
    "==========================================================================================\n\n"<<
    "STRING-BASED Chessboard used for GamePlay \n\nPieces are: \n\n"<<
    "White: WP-White Pawns WN-White Knight(Horse) WB-WhiteBishop WQ-WhiteQueen WR-WhiteRook WK-White King \n\n"<<
    "Black: Similar to White just starting letter is B instead (i.e BP,BN,BB,BQ,BK,BR)\n\n"<<
    "1. Select the square of the piece to move using the coordinates(a-h,1-8)\nSimilar to Std ChessNotation displayed in the board \n"
    <<"Example Select e2 for White King's pawn (WP5) \n\n"<<"2. After which Select the square to go i.e for the previous ex : e4 \n\n"
    <<"3. You will see the board updated with e2-e4 move being made (WP5 move being updated)\n\n"
    <<"4. Use X key to Exit the game \n\n"<<
    "5. Similar for Black as well \n\n"<<
    "6. Rules follow all the Standard Rules for the chessgame (CHECK,CHECKMATE,CASTLING,PROMOTION) \n\n\n"<<

    "SAMPLE GAME: Type All these 2-Letter Strings One-by-one in order at every REQUEST FOR INPUT \n"<<
    "e2 e4 e7 e5 g1 f3 g8 f6 f1 c4 f8 c5 f3 e5 f6 e4 d1 h5 h8 g8 h5 f7 \n\n"<<
    "if you Typed correctly Game Results in Checkmate \n"
    "==========================================================================================";
}
