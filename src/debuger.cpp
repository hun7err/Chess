#include "figures.cpp"
#include "chess.cpp"

using namespace std;

Pos NPos( short int x, short int y){
    Pos nPos; nPos.set(x,y);
    return nPos;
}

void pisz(Chess gra){
    for(int i=0;i<64;i++){
        if(!(i%8))
            cout<<endl<<(i/8+1)<<"\t";
        if(gra.Board[(i%8)*8+i/8]!=NULL)
            cout<<gra.Board[(i%8)*8+i/8]->no<<' '<<gra.Board[(i%8)*8+i/8]->color<<"\t";
        else
            cout<<"_ _\t";
    }
    cout<<endl;
    cout<<"y/x\t";
    for(int i=1;i<9;i++)
        cout<<i<<"\t";
    cout<<endl;
}

void pisz(vector<Pos> x){
    cout<<endl;
    for(int i=0;i<x.size();i++)
    cout<<x[i].x()+1<<' '<<x[i].y()+1<<endl;

}

int main(){
    Chess gra;
    gra.move(NPos(1,0),NPos(0,2));
    gra.move(NPos(1,7),NPos(0,5));
    gra.move(NPos(3,1),NPos(3,3));
    gra.move(NPos(3,6),NPos(3,4));
    gra.move(NPos(3,0),NPos(3,2));
    gra.move(NPos(3,7),NPos(3,5));
    gra.move(NPos(2,0),NPos(3,1));
    gra.move(NPos(2,7),NPos(3,6));
    pisz(gra);
    pisz(gra.poss_moves(NPos(4,0)));

    gra.move(NPos(4,0),NPos(2,0));
    pisz(gra);
    pisz(gra.poss_moves(NPos(4,7)));
    gra.move(NPos(4,7),NPos(2,7));
    pisz(gra);
    cout<<"_____________________________________________\n";
   // pisz(gra.figures_to_move());
    //gra.move(NPos(3,1),NPos(3,3));
  //  pisz(gra);
    gra.undo();
    pisz(gra);
    gra.undo();
    pisz(gra);
    //pisz2(gra);
    return 0;
}
