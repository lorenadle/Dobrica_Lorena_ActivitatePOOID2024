#include<iostream>
#include<string>
using namespace std;

using namespace std;
class Autobuz {
private:
	static int nrAutobuze; //contorizează automat numărul de autobuze create
	const int idAutobuz; //id-ul unic al autobuzului
	int	capacitate; //numărul de persoane care pot fi îmbarcate în autobuz pe locuri
	int	nrPersoaneImbarcate;//numărul de persoane aflate în autobuz. Nu poate fi mai mare decât capacitatea autobuzului;
	char* producator;//numele producătorului autobuzului


public:
	//constructor fără parametri
	Autobuz() :idAutobuz(++nrAutobuze) {
		this->capacitate = 50;
		this->nrPersoaneImbarcate = 10;
		this->producator = new char[strlen("Mercedes") + 1];
		strcpy_s(this->producator, strlen("Mercedes") + 1, "Mercedes");
		
	}
	//constructor cu parametri.Constructorul cu parametri conține validări pentru parametrii primiți.

	Autobuz(int capacitate, int nrPersoaneImbarcate): idAutobuz(++nrAutobuze) {
		if (capacitate <= 0) {
			cout << this->capacitate << "Capacitatea autobuzului trebuie sa fie mai mare decat 0! " << endl;
		}
		if ( nrPersoaneImbarcate > capacitate) {
			cout  << "Numarul de persoane imbarcate trebuie sa fie intre mai mic decat capacitatea autobuzului! " << endl;
			

		}
		this->capacitate = capacitate;
		this->nrPersoaneImbarcate = nrPersoaneImbarcate;
		this->producator = new char[strlen("Marca necunoscuta") + 1];
		strcpy_s(this->producator, strlen("Marca necunoscuta") + 1, "Marca necunoscuta");
	
	}

	// destructor
	~Autobuz() {
		cout << endl << "S-a apelat destructorul!";
		if (this->producator != nullptr)
			delete[] this->producator;
	}


	// constructorul de copiere
	Autobuz(const Autobuz& a) : idAutobuz(++nrAutobuze) {
		capacitate = a.capacitate;
		nrPersoaneImbarcate = a.nrPersoaneImbarcate;

		if (a.producator != nullptr) {
			producator = new char[strlen(a.producator) + 1];
			strcpy_s(producator, strlen(a.producator) + 1, a.producator);
		}
		else {
			producator = nullptr;
		}
	}

	// metode accesor(get si set) pentru nrAutobuze
	static int getnrAutobuze() {
		return nrAutobuze;
	}
	static void setnrAutobuze(int _nrAutobuze) {
		nrAutobuze = _nrAutobuze;
	}

	// metode accesor(get si set) pentru producator
	const char* getProducator() const {
		return producator;
	}

	void setProducator(const char* producator) {
		delete[] this->producator;
		this->producator = new char[strlen(producator) + 1];
		strcpy_s(this->producator, strlen(producator) + 1, producator);
	}

	void afisareAutobuz() {
		cout << "Autobuzul cu id-ul "<< this->idAutobuz << " si capacitatea " << this->capacitate;
		if (this->nrPersoaneImbarcate > 0) {
			cout << " are " << this->nrPersoaneImbarcate << " persoane imbarcate";
			if (this->producator != nullptr) {		
					cout << " si producatorul acestuia este: " << this->producator << endl;
			}
		}
			}



	// Operator de atribuire
	Autobuz& operator=(const Autobuz& a) {
		if (this != &a) {
			delete[] producator;

			capacitate = a.capacitate;
			nrPersoaneImbarcate = a.nrPersoaneImbarcate;

			producator = new char[strlen(a.producator) + 1];
			strcpy_s(producator, strlen(a.producator) + 1, a.producator);
		}
		return *this;
	}

	// supraîncarcarcare operator de cast la int care determină numărul de persoane urcate deja în autobuz
	operator int() const {
		return nrPersoaneImbarcate;

	}


	// supraîncarcare operator> care va compara două autobuze după capacitatea acestora
	bool operator>(const Autobuz& a) const {
		return capacitate > a.capacitate;
	}



	// Suprascriere operator <<
	friend ostream& operator<<(ostream& out, const Autobuz& a) {
		out << "ID-ul autobuzului este: " << a.idAutobuz << "; Capacitatea este: " << a.capacitate
			<< "; Numarul persoanelor imbarcate este: " << a.nrPersoaneImbarcate
			<< "; Producatorul este: " << (a.producator ? a.producator : "Necunoscut");
		return out;
	}

	// metoda getNumarLocuriLibere() care calculează și returnează numărul de locuri libere rămase în autobuz
		int getNumarLocuriLibere() const {
		return capacitate - nrPersoaneImbarcate;





	}


};
//initializare nrAutobuze
int Autobuz::nrAutobuze = 0;
void main() {
	//constructor fără parametri
	Autobuz autobuz1;
	autobuz1.afisareAutobuz();

	//constructor cu parametri.Testare capacitate mai mare decat nrPersoaneImbarcate
	Autobuz autobuz2(100, 40);
	autobuz2.afisareAutobuz();

	//constructor cu parametri. estare capacitate mai mica decat nrPersoaneImbarcate
	Autobuz autobuz3(20, 40);
	autobuz3.afisareAutobuz();

	// constructorul de copiere
	Autobuz autobuz4= autobuz1;
	autobuz4.afisareAutobuz();


	// Testare get si set pt 2 atribute
	// Testare getnrAutobuze()
	cout << "Numarul autobuzelor pana in prezent este " << autobuz4.getnrAutobuze() << endl;

	// Testare getProducator()
	cout << "Producatorul acestui autobuz este " << autobuz1.getProducator() << endl;

	// Test operatorul= (de atribuire)
	autobuz1 = autobuz2;
	cout << "Autobuz 1 dupa atribuire este: " << autobuz1 << endl;

	// Testare getProducator()
	cout << "Producatorul acestui autobuz este " << autobuz1.getProducator() << endl;


	// Testare numar locuri libere
		int locuriLibere = autobuz4.getNumarLocuriLibere();
	cout << "Locuri libere in Autobuzul 4: " << locuriLibere << endl;

	// Test supraîncarcarcare operator de cast la int
	int nrPersoane = (int) autobuz4;
	cout << "Numarul persoanelor imbarcate in Autobuzul 4 este: : " << nrPersoane << endl;

	// Test greater than operator
	bool comparatie_capacitate = autobuz2 > autobuz1;
	cout << "Este capacitatea autobuzului 2 mai mare decat capacitatea autobuzului 1? " << (comparatie_capacitate ? "DA" : "NU") << endl;
}
	