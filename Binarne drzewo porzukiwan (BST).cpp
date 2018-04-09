#include <iostream>
#include <cstdlib>

struct wezel
{
    int wartosc;
    wezel *prawo;
    wezel *lewo;
};
wezel* przedostatni_lewy(wezel *k);
wezel* skrajny_lewy(wezel *k);
wezel* usuwanie(wezel *&k,int x);
wezel* lewe_dziecko_prawego(wezel *k);
void dodawanie(wezel *k);
void BST_dodawanie(wezel *&k , int x);
void drukowanie(wezel *k, int ile);
bool szukanie(wezel *k, int x);

void menu(wezel *k);

using namespace std;


int main()
{
    wezel *korzen = NULL;
    menu(korzen);
    return 0;
}

void menu(wezel *k)
{
int opcja;
int ile=0;

    cout<<"---------------------------------------"<<endl
        <<"                 MENU                  "<<endl
        <<"---------------------------------------"<<endl
        <<"                                       "<<endl
        <<"           1. Dodaj wartosc"<<endl
        <<"           2. Usun wartosc"<<endl
        <<"           3. Drukuj drzewo"<<endl
        <<"                                       "<<endl
        <<"---------------------------------------"<<endl;

    while(!(cin>>opcja))
    {
        cin.clear();
        cin.sync();
        cout << "Bledne dane"<<endl;
    }
    system("cls");

    switch(opcja)
    {
        case 1:
            dodawanie(k);
            break;
        case 2:
            int x;
            drukowanie(k, ile);
            cout<<"Podaj wartosc, ktora chcesz usunac:";
            while(!(cin>>x))
            {
                cin.clear();
                cin.sync();
                cout << "Bledne dane"<<endl;
            }
            system("cls");
            usuwanie(k,x);
            menu(k);
            break;
        case 3:
            drukowanie(k, ile);
            system("pause");
            system("cls");
            menu(k); break;
        default:
            cout<<"Podano niepoprawny numer!"<<endl<<endl;
            menu(k);
    }
}

void dodawanie(wezel *k)
{
    int wstawiany;
    cout << "Podaj wartosc, ktora chcesz dodac:";
    while(!(cin>>wstawiany))
    {
        cin.clear();
        cin.sync();
        cout << "Bledne dane"<<endl;
    }

    if (szukanie(k, wstawiany) == 0)
    {
        menu(k);
        return;
    }
    BST_dodawanie(k,wstawiany);

    system("cls");
    cout << "Wartosc zostala dodana."<<endl<<endl;
    menu(k);

}
void  BST_dodawanie(wezel *&k , int x)
{
    if ( k == NULL)
    {
        wezel *nowy = new wezel;
        nowy->wartosc = x;
        nowy->lewo= NULL;
        nowy->prawo = NULL;
        k = nowy;
    }
    else if (x >= k->wartosc)BST_dodawanie(k->prawo,x);
    else BST_dodawanie(k->lewo,x);
}

void drukowanie(wezel *k,int ile)
{
    ile++;

    if (k != NULL) {

    if (k->prawo != NULL);
        drukowanie(k->prawo, ile);
    for (int i=0; i<ile; i++)
        cout<<"    ";
    cout << k->wartosc<<endl;
    drukowanie(k->lewo, ile);
}
}

wezel* usuwanie(wezel *&k, int x)
{
    if (k == NULL)
    {
        system("cls");
        cout << " Brak wezla "<<endl;
    }
    else if (k->wartosc == x)
    {

        if ((k->lewo == NULL) && (k->prawo == NULL))
        {
            k = NULL;
            system("cls");
            cout << " USUNIETO "<<endl;
        }
        else if ((k->lewo != NULL) && (k->prawo == NULL))
        {
            k = k->lewo;
            system("cls");
            cout << " USUNIETO "<<endl;
        }
        else if ((k->lewo == NULL) && (k->prawo != NULL))
        {
            k = k->prawo;
            system("cls");
            cout << " USUNIETO "<<endl;
        }
        else if ( lewe_dziecko_prawego(k->prawo) == NULL )
        {
            wezel *y = new wezel;
            y = k->lewo;
            k = k->prawo;
            k->lewo = y;

            system("cls");
            cout << " USUNIETO "<<endl;
        }
        else if ( lewe_dziecko_prawego(k->prawo) != NULL)
        {
            wezel *z = new wezel;
            z = skrajny_lewy(k->prawo);
            k->wartosc=z->wartosc;
            przedostatni_lewy(k->prawo);

            system("cls");
            cout << " USUNIETO "<<endl;
        }
    }
    else
    if (x < k->wartosc)
    usuwanie(k->lewo,x);
    else
    usuwanie(k->prawo,x);
}

wezel* skrajny_lewy(wezel *k)
{
    if (k->lewo == NULL)
    {
        return k;
    }
    else
        return skrajny_lewy(k->lewo);
}

wezel* lewe_dziecko_prawego(wezel *k)
{
   return k->lewo;
}

bool szukanie(wezel *k, int x)
{
    if (k == NULL)
        return 1;
    else if (k->wartosc == x)
    {
        cout << "Wartosc juz istnieje"<<endl;
        return 0;
    }
    else if (x < k->wartosc)
        return szukanie(k->lewo,x);
    else
        return szukanie(k->prawo,x);
}

wezel* przedostatni_lewy(wezel *k)
{
    if (k->lewo->lewo == NULL)
    {
        k->lewo=NULL;
    }
    else
        return przedostatni_lewy(k->lewo);
}
