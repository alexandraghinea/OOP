#include <iostream>
#include <cstring>
using namespace std;

class Data{
    int zi;
    char luna[20];
    int an;
public:
    Data();
    Data(const Data &);
    Data(int x, char* y, int z);
    ~Data();
    Data& operator =(const Data&);
    friend istream & operator >>(istream & in, Data & d);
    friend ostream & operator <<(ostream & out, const Data & d);
    void setzi (int x)//setteri pentru atribuire
    {
        this->zi = x;
    }
    void setluna (char *y)
    {
        strcpy(this->luna, y);
    }
    void setan (int z)
    {
        this->an = z;
    }
};

Data::Data()
{
    zi = an = 0;
    strcpy(luna, "");
}

Data::Data(int x, char* y, int z)
{
    this->zi = x;
    strcpy(this->luna, y);
    this->an = z;
}

Data::Data(const Data &ob)
{
    zi = ob.zi;
    an = ob.an;
    strcpy(luna, ob.luna);
}

Data::~Data()= default;

Data& Data::operator =(const Data & ob)
{
    if (this != &ob)
    {
        this->zi = ob.zi;
        strcpy(this->luna, ob.luna);
        this->an = ob.an;
    }
    return *this;
}

istream & operator >>(istream & in, Data & d)
{
    in>>d.zi;
    in.get();
    in>>d.luna;
    in.get();
    in>>d.an;
    in.get();
    return in;
}

ostream & operator <<(ostream & out, const Data & d)
{
    out<<" "<<d.zi<<" "<<d.luna<<" "<<d.an;
    return out;
}

//*****************

class Actor{
    char* nume;
    Data data_nasterii;
public:
    Actor();
    Actor(const Actor &);
    Actor(char *nume, Data d);
    Actor(char *nume, int zi, char *luna, int an);
    ~Actor();
    Actor& operator =(const Actor &);
    friend istream & operator >>(istream& in, Actor & Altul);
    friend ostream & operator <<(ostream& out,const Actor & Altul);
};

Actor:: Actor()
{
    this->nume = new char[strlen("anonim")+1];
        strcpy(this->nume, "anonim");
    this->data_nasterii;
}

Actor:: Actor(const Actor & ob)
{
    if(this != &ob)
    {
        nume= new char[strlen(ob.nume)+1];
        for(int i=0; i<strlen(ob.nume)+1; i++)
            nume[i] = ob.nume[i];
        this->data_nasterii = ob.data_nasterii;
    }
}

Actor:: Actor(char *nume, Data d )
{
    this->nume = new char[strlen(nume)+1];
    for(int i=0; i<strlen(nume)+1; i++)
        this->nume[i] = nume[i];
    this->data_nasterii = d;

}

Actor::Actor(char *nume, int zi, char *luna, int an)
{
    this->nume = new char[strlen(nume)+1];
    for(int i=0; i<strlen(nume)+1; i++)
        this->nume[i] = nume[i];
    data_nasterii.setzi(zi);
    data_nasterii.setluna(luna);
    data_nasterii.setan(an);

}

Actor::~Actor()
{
    if (nume)
    {
        delete[] nume;
        nume = "";
    }
}
Actor &Actor::operator =(const Actor & ob)
{
    if(this != &ob)
     {
        if(this->nume != NULL)
                delete[] this->nume;
        this->nume = new char[strlen(ob.nume)+1];
        strcpy(this->nume,ob.nume);
        this->data_nasterii = ob.data_nasterii;
     }
        return *this;
}
istream & operator >>(istream & in, Actor & Altul)
{
    char s[255];
    in.getline(s,255);
    if(Altul.nume != NULL)
        delete [] Altul.nume;
    Altul.nume = new char[strlen(s)+1];
    strcpy(Altul.nume, s);
    in>>Altul.data_nasterii;
    return in;

}

ostream & operator <<(ostream & out, const Actor & Altul)
{
    out<<Altul.nume;
    out<<Altul.data_nasterii;
    return out;
}

//***************

class Film{
    char titlu[50];
    int nrActori;
    Actor *Act;
public:
    Film();
    Film(char *t);
    Film(const Film &);
    ~Film();
    Film& operator =(const Film &);
    friend Film operator +=(Film & f, const Actor &);
    friend istream & operator >>(istream& in, Film & film);
    friend ostream & operator <<(ostream& out, const Film & film);
};

Film::Film()
{
    strcpy(this->titlu, "");
    this->Act = NULL;
    this->nrActori = 0;
}

Film::Film(char *t)
{
    strcpy(titlu,t);
    this->Act = NULL;
    this->nrActori = 0;
}

Film::Film(const Film & ob)
{
    strcpy(titlu, ob.titlu);
    nrActori = ob.nrActori;
    Act = new Actor[nrActori];
    for(int i=0; i<nrActori; i++)
        Act[i] = ob.Act[i];

}

Film& Film::operator =(const Film & ob)
{
    if (this != &ob)
    {
        this->nrActori = ob.nrActori;
        strcpy(this->titlu, ob.titlu);
        if(this->Act)
            delete [] Act;
        Act = new Actor[this->nrActori];
        for(int i=0; i<this->nrActori; i++)
            this->Act[i] = ob.Act[i];
    }
    return *this;
}

Film operator +=(Film & f, const Actor & noulAct)
{
        Actor* aux;
        aux = new Actor[f.nrActori];
        for(int i=0; i<f.nrActori; i++)
            aux[i] = f.Act[i];
        if(f.Act != NULL)
            delete[] f.Act;
        f.nrActori++;
        f.Act = new Actor[f.nrActori];
        for(int i=0; i<f.nrActori-1; i++)
            f.Act[i] = aux[i];
        f.Act[f.nrActori-1] = noulAct;
        if(aux != NULL)
            delete[] aux;
        return f;
}

Film::~Film()
{
    if(this->Act)
        delete[] this->Act;
}

istream & operator >>(istream& in, Film & film)
{
    in.getline(film.titlu, 50);
    in>>film.nrActori;
    in.get();
    if(film.Act != NULL)
        delete []film.Act;
    film.Act = new Actor[film.nrActori];
    for(int i=0; i<film.nrActori; i++)
        in>>film.Act[i];
    return in;
}

ostream & operator <<(ostream& out, const Film & film)
{
    out<<film.titlu<<" "<<film.nrActori<<endl;
    for (int i=0; i<film.nrActori; i++)
           out<<film.Act[i]<<endl;

    return out;
}

int main()
{
    Data d1(15, "iulie", 1975), d2 = d1;
    Actor a1("Ionescu", d1), a2("Popescu", 2, "ianuarie", 1980);
    Film  f1("Matrix"), f2, f3;
    f1 += a1;
    f1 += a2;
    cout<<f1;
    cin>>f2;
    f3 = f2;
    cout<<f3;
    return 0;
}
