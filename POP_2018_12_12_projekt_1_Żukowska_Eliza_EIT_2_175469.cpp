#include <iostream>
#include <cstdlib>
#include <iomanip>


using namespace std;

const int n = 20;
const int m = 50;



void rysujMape(char tab[n][m])
{
    cout<<setw(25)<<"SOKOBAN"<<endl;
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = 0 ; j < m ; j++)
        {
            cout<<tab[i][j];
        }
        cout<<endl;
    }
}

char pion = 0xBA;
char poziom = 0xCD;
char gl = 0xC9;
char gp = 0xBB;
char dl = 0xC8;
char dp = 0xBC;
char tlo = ' ';
char R = 'R';
char P = 'x';
char M = 'O';
char Koniec = 'X';
int x;

struct obiekt
{
    int pozy;
    int pozx;
    char znakObiektu;
};
obiekt gracz;
obiekt paczka;
obiekt meta;


bool czyObiektWjechalWSciane(char sciana)
{
    return sciana==pion||sciana==poziom||sciana==gl||sciana==gp||sciana==dl||sciana==dp;
}

bool czyObiekt1NadObiektem2(obiekt obiekt1,obiekt obiekt2,char mapa[n][m])
{
    return obiekt1.znakObiektu==mapa[obiekt2.pozy-1][obiekt2.pozx];
}
bool czyObiekt1PodObiektem2(obiekt obiekt1, obiekt obiekt2,char mapa[n][m])
{
    return obiekt1.znakObiektu==mapa[obiekt2.pozy+1][obiekt2.pozx];
}
bool czyObiekt1PoLewejObiektu2(obiekt obiekt1, obiekt obiekt2,char mapa[n][m])
{
    return obiekt1.znakObiektu==mapa[obiekt2.pozy][obiekt2.pozx-1];
}
bool czyObiekt1PoPrawejObiektu2(obiekt obiekt1, obiekt obiekt2,char mapa[n][m])
{
    return obiekt1.znakObiektu==mapa[obiekt2.pozy][obiekt2.pozx+1];
}

void rysujObiekt1ZamiastObiektu2(obiekt obiekt1, obiekt obiekt2, char mapa[n][m])
{
    mapa[obiekt2.pozy][obiekt2.pozx]=obiekt1.znakObiektu;
}
void rysujKoniec(obiekt paczka,char mapa[n][m])
{
    mapa[paczka.pozy][paczka.pozx]=Koniec;
}

void przesunGracza(char mapa[n][m], int przesunieciey, int przesunieciex)
{
    mapa[gracz.pozy][gracz.pozx]=tlo;
    gracz.pozy+=przesunieciey;
    gracz.pozx+=przesunieciex;
    mapa[gracz.pozy][gracz.pozx]=R;
}
void przesunPaczke(char mapa[n][m], int przesunieciey, int przesunieciex)
{
    mapa[paczka.pozy][paczka.pozx]=R;
    paczka.pozy+=przesunieciey;
    paczka.pozx+=przesunieciex;
    mapa[paczka.pozy][paczka.pozx]=P;
}

void ruch(char mapa[n][m])
{
    char przyciskKtoryWcisnalGracz;
    while(true)
    {
        cin>>przyciskKtoryWcisnalGracz;
        if(przyciskKtoryWcisnalGracz == 'w')
        {
            if(czyObiektWjechalWSciane(mapa[gracz.pozy-1][gracz.pozx]))
            {
                continue;
            }
            else if(czyObiektWjechalWSciane(mapa[paczka.pozy-1][paczka.pozx]))
            {
                if(czyObiekt1NadObiektem2(paczka,gracz,mapa))
                {
                    continue;
                }
                else
                {
                    przesunGracza(mapa,-1,0);
                }
                break;
            }
            else if(czyObiekt1NadObiektem2(paczka,gracz,mapa))
            {
                if(czyObiekt1NadObiektem2(meta,paczka,mapa))
                {
                    przesunPaczke(mapa,-1,0);
                    rysujKoniec(paczka,mapa);
                    przesunGracza(mapa,-1,0);
                }
                else
                {
                    przesunPaczke(mapa,-1,0);
                    przesunGracza(mapa,-1,0);
                }
                break;
            }
            else if(czyObiekt1NadObiektem2(meta,gracz,mapa))
            {
                continue;
            }
            else
            {
                przesunGracza(mapa,-1,0);
                break;
            }
        }
        else if(przyciskKtoryWcisnalGracz == 's')
        {
            if(czyObiektWjechalWSciane(mapa[gracz.pozy+1][gracz.pozx]))
            {
                continue;
            }
            else if(czyObiektWjechalWSciane(mapa[paczka.pozy+1][paczka.pozx]))
            {
                if(czyObiekt1PodObiektem2(paczka,gracz,mapa))
                {
                    continue;
                }
                else
                {
                    przesunGracza(mapa,1,0);
                }
                break;
            }
            else if(czyObiekt1PodObiektem2(paczka,gracz,mapa))
            {
                if(czyObiekt1PodObiektem2(meta,paczka,mapa))
                {
                    przesunPaczke(mapa,1,0);
                    rysujKoniec(paczka,mapa);
                    przesunGracza(mapa,1,0);
                }
                else
                {
                    przesunPaczke(mapa,1,0);
                    przesunGracza(mapa,1,0);
                }
                break;
            }
            else if(czyObiekt1PodObiektem2(meta,gracz,mapa))
            {
                continue;
            }
            else
            {
                przesunGracza(mapa,1,0);
                break;
            }
        }
        else if(przyciskKtoryWcisnalGracz == 'a')
        {
            if(czyObiektWjechalWSciane(mapa[gracz.pozy][gracz.pozx-1]))
            {
                continue;
            }
            else if(czyObiektWjechalWSciane(mapa[paczka.pozy][paczka.pozx-1]))
            {
                if(czyObiekt1PoLewejObiektu2(paczka,gracz,mapa))
                {
                    continue;
                }
                else
                {
                    przesunGracza(mapa,0,-1);
                }
                break;
            }
            else if(czyObiekt1PoLewejObiektu2(paczka,gracz,mapa))
            {
                if(czyObiekt1PoLewejObiektu2(meta,paczka,mapa))
                {
                    przesunPaczke(mapa,0,-1);
                    rysujKoniec(paczka,mapa);
                    przesunGracza(mapa,0,-1);
                }
                else
                {
                    przesunPaczke(mapa,0,-1);
                    przesunGracza(mapa,0,-1);
                }
                break;
            }
            else if(czyObiekt1PoLewejObiektu2(meta,gracz,mapa))
            {
                continue;
            }
            else
            {
                przesunGracza(mapa,0,-1);
                break;
            }
        }
        else if(przyciskKtoryWcisnalGracz == 'd')
        {
            if(czyObiektWjechalWSciane(mapa[gracz.pozy][gracz.pozx+1]))
            {
                continue;
            }
            else if(czyObiektWjechalWSciane(mapa[paczka.pozy][paczka.pozx+1]))
            {
                if(czyObiekt1PoPrawejObiektu2(paczka,gracz,mapa))
                {
                    continue;
                }
                else
                {
                    przesunGracza(mapa,0,1);
                }
                break;
            }
            else if(czyObiekt1PoPrawejObiektu2(paczka,gracz,mapa))
            {
                if(czyObiekt1PoPrawejObiektu2(meta,paczka,mapa))
                {
                    przesunPaczke(mapa,0,1);
                    rysujKoniec(paczka,mapa);
                    przesunGracza(mapa,0,1);
                }
                else
                {
                    przesunPaczke(mapa,0,1);
                    przesunGracza(mapa,0,1);
                }
                break;
            }
            else if(czyObiekt1PoPrawejObiektu2(meta,gracz,mapa))
            {
                continue;
            }
            else
            {
                przesunGracza(mapa,0,1);
                break;
            }
        }
        else if(przyciskKtoryWcisnalGracz == 'q')
        {
            exit(0);
        }
        else if(przyciskKtoryWcisnalGracz == '?')
        {
            cout<<"Sokoban polega na poruszaniu sie robotnikiem po magazynie. Robotnik moze pchac paczki (x). Wygrywasz gre, gdy wszystkie paczki beda na mecie (O)."<<endl;
        }
        else
        {
            cout<<"Nieprawidlowy znak"<<endl;
        }
    }
}

bool czyGraSkonczona(char mapa[n][m])
{
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = 0 ; j < m ; j++)
        {
            if(mapa[i][j]==Koniec)
            {
                return true;
            }
        }
    }
    return false;

}

void graj(char mapa[n][m])
{
    while(!czyGraSkonczona(mapa))
    {
        system( "cls" );
        rysujMape(mapa);
        ruch(mapa);
    }
    system( "cls" );
    rysujMape(mapa);
    cout<<"Gratulacje!"<<endl;
}

int main()
{
    gracz.znakObiektu=R;
    paczka.znakObiektu=P;
    meta.znakObiektu=M;


    char t[n][m]= {{gl,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,gp},
        {pion,R,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,pion},
        {pion,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,pion},
        {pion,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,pion},
        {pion,tlo,M,tlo,tlo,tlo,tlo,P,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,pion},
        {pion,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,pion},
        {pion,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,pion},
        {pion,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,pion},
        {dl,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,dp}
    };

    char t1[n][m]= {{tlo,tlo,tlo,tlo,tlo,gl,poziom,poziom,poziom,poziom,gp},
        {tlo,tlo,tlo,tlo,tlo,pion,R,tlo,tlo,tlo,pion},
        {gl,poziom,poziom,poziom,poziom,dp,tlo,tlo,tlo,tlo,dl,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,gp},
        {pion,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,pion},
        {pion,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,pion},
        {pion,tlo,tlo,tlo,tlo,tlo,tlo,P,tlo,tlo,tlo,gl,poziom,poziom,poziom,poziom,gp,tlo,tlo,tlo,tlo,tlo,tlo,pion},
        {pion,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,pion,tlo,tlo,tlo,tlo,pion,tlo,tlo,tlo,tlo,tlo,tlo,pion},
        {dl,poziom,poziom,poziom,gp,tlo,tlo,tlo,tlo,tlo,tlo,pion,tlo,tlo,tlo,tlo,pion,tlo,tlo,tlo,tlo,tlo,tlo,pion},
        {tlo,tlo,tlo,tlo,pion,tlo,tlo,tlo,tlo,tlo,tlo,dl,poziom,poziom,poziom,poziom,dp,tlo,tlo,tlo,tlo,tlo,tlo,dl,poziom,poziom,poziom,poziom,poziom,gp},
        {tlo,tlo,tlo,tlo,pion,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,pion},
        {tlo,tlo,tlo,tlo,pion,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,pion},
        {tlo,tlo,tlo,tlo,pion,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,M,tlo,tlo,tlo,tlo,tlo,tlo,pion},
        {tlo,tlo,tlo,tlo,dl,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,dp},
    };

    char t2[n][m]= {{tlo,tlo,tlo,tlo,tlo,gl,poziom,poziom,poziom,poziom,gp,tlo,tlo,tlo,tlo,tlo,tlo,gl,poziom,poziom,poziom,poziom,poziom,gp},
        {tlo,tlo,tlo,tlo,tlo,pion,tlo,tlo,tlo,tlo,pion,tlo,tlo,tlo,tlo,tlo,tlo,pion,tlo,tlo,tlo,tlo,tlo,pion},
        {gl,poziom,poziom,poziom,poziom,dp,tlo,tlo,tlo,tlo,dl,poziom,poziom,poziom,poziom,poziom,poziom,dp,tlo,tlo,tlo,tlo,tlo,pion},
        {pion,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,dl,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,gp},
        {pion,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,pion},
        {pion,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,gl,poziom,poziom,poziom,poziom,gp,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,dl,poziom,poziom,poziom,poziom,poziom,gp},
        {pion,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,pion,tlo,tlo,tlo,tlo,pion,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,P,tlo,tlo,tlo,tlo,tlo,pion},
        {dl,poziom,poziom,poziom,gp,tlo,tlo,tlo,tlo,tlo,tlo,pion,tlo,tlo,tlo,tlo,pion,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,pion},
        {tlo,tlo,tlo,tlo,pion,tlo,tlo,tlo,tlo,tlo,tlo,pion,tlo,tlo,tlo,tlo,dl,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,dp},
        {tlo,tlo,tlo,tlo,pion,tlo,tlo,R,tlo,tlo,tlo,dl,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,gp},
        {tlo,tlo,tlo,tlo,pion,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,M,tlo,pion},
        {tlo,tlo,tlo,tlo,pion,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,pion},
        {tlo,tlo,tlo,tlo,dl,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,dp},
    };

    char t3[n][m]= {{tlo,tlo,tlo,tlo,tlo,tlo,tlo,gl,poziom,poziom,poziom,poziom,poziom,poziom,gp,tlo,tlo,tlo,gl,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,gp},
        {tlo,tlo,tlo,tlo,tlo,tlo,tlo,pion,tlo,tlo,tlo,tlo,tlo,tlo,pion,tlo,tlo,tlo,pion,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,pion},
        {tlo,tlo,tlo,tlo,tlo,tlo,tlo,pion,tlo,tlo,tlo,tlo,tlo,tlo,pion,tlo,tlo,tlo,pion,tlo,P,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,pion,tlo,gl,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,gp},
        {gl,poziom,poziom,poziom,poziom,poziom,poziom,dp,tlo,tlo,tlo,tlo,tlo,tlo,dl,poziom,poziom,poziom,dp,tlo,tlo,tlo,gl,poziom,poziom,poziom,gp,tlo,tlo,tlo,pion,tlo,pion,tlo,tlo,tlo,tlo,tlo,tlo,tlo,M,pion},
        {pion,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,pion,tlo,tlo,tlo,pion,tlo,tlo,tlo,pion,tlo,pion,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,pion},
        {pion,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,pion,tlo,tlo,tlo,pion,tlo,tlo,tlo,pion,tlo,pion,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,pion},
        {pion,tlo,tlo,tlo,gl,poziom,gp,tlo,tlo,tlo,gl,poziom,poziom,poziom,gp,tlo,tlo,tlo,tlo,tlo,tlo,tlo,dl,poziom,poziom,poziom,dp,tlo,tlo,tlo,pion,tlo,dl,poziom,gp,tlo,tlo,gl,poziom,poziom,poziom,dp},
        {pion,tlo,tlo,tlo,pion,tlo,pion,tlo,tlo,tlo,pion,tlo,tlo,tlo,pion,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,pion,tlo,tlo,tlo,pion,tlo,tlo,pion},
        {pion,tlo,tlo,tlo,pion,tlo,pion,tlo,tlo,tlo,pion,tlo,tlo,tlo,pion,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,pion,tlo,tlo,tlo,pion,tlo,tlo,pion},
        {pion,tlo,tlo,tlo,pion,tlo,pion,tlo,R,tlo,pion,tlo,tlo,tlo,pion,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,pion,tlo,tlo,tlo,pion,tlo,tlo,pion},
        {pion,tlo,tlo,tlo,pion,tlo,dl,poziom,poziom,poziom,dp,tlo,tlo,tlo,dl,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,dp,tlo,tlo,tlo,pion,tlo,tlo,pion},
        {pion,tlo,tlo,tlo,dl,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,dp,tlo,tlo,pion},
        {pion,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,pion},
        {pion,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,tlo,pion},
        {dl,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,poziom,dp}
    };

    int numer;
    cout<<setw(25)<<"SOKOBAN"<<endl;
    cout<<"Sterowanie [w,s,a,d]"<<endl;
    cout<<"Wyjscie z gry [q]"<<endl;
    cout<<"Pomoc [?]"<<endl;
    cout<<"Wybierz mape(1,2,3): ";
    cin>>numer;
    if(numer == 1)
    {
        meta.pozy=9;
        meta.pozx=22;
        gracz.pozy=1;
        gracz.pozx=6;
        paczka.pozy=5;
        paczka.pozx=7;
        graj(t1);
    }
    else if(numer == 2)
    {
        meta.pozy=10;
        meta.pozx=40;
        paczka.pozy=6;
        paczka.pozx=33;
        gracz.pozy=9;
        gracz.pozx=7;
        graj(t2);
    }
    else if(numer == 11)
    {
        meta.pozx=2;
        meta.pozy=4;
        paczka.pozx=7;
        paczka.pozy=4;
        gracz.pozy=1;
        gracz.pozx=1;
        graj(t);
    }
    else if(numer == 3)
    {
        meta.pozy=3;
        meta.pozx=40;
        paczka.pozy=2;
        paczka.pozx=20;
        gracz.pozy=9;
        gracz.pozx=8;
        graj(t3);
    }
    else
    {
        cout<<"Nie ma takiej mapy"<<endl;
    }
    return 0;
}
