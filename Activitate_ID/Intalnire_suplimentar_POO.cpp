#include<iostream>
#include<string>

using namespace std;

class Masina {
private:
	const int id;
	static int nrMasini;
	string marca;
	int nrComponente;
	float* preturi;
public:
	Masina() :id(++nrMasini) {
		this->marca = "Necunoscuta";
		this->nrComponente = 0;
		this->preturi = nullptr;
	}

	Masina(string _marca, int nrComponente, float* preturi) :id(++nrMasini) {
		marca = _marca;
		this->nrComponente = nrComponente;
		//shallow copy
		//this->preturi = preturi;

		//deep copy
		this->preturi = new float[nrComponente];
		for (int i = 0; i < nrComponente; i++) {
			this->preturi[i] = preturi[i];
		}
		delete[] preturi;
	}

	Masina(const Masina& m) :id(++nrMasini) {
		this->marca = m.marca;
		this->nrComponente = m.nrComponente;
		this->preturi = new float[m.nrComponente];
		for (int i = 0; i < m.nrComponente; i++) {
			this->preturi[i] = m.preturi[i];
		}
	}

	const Masina& operator=(const Masina& m) {
		if (this == &m) {
			return *this;
		}
		this->marca = m.marca;
		this->nrComponente = m.nrComponente;
		if (this->preturi != nullptr) {
			delete[]this->preturi;
		}
		this->preturi = new float[m.nrComponente];
		for (int i = 0; i < m.nrComponente; i++) {
			this->preturi[i] = m.preturi[i];
		}
		return *this;
	}

	//masina3 += 1000;
	Masina operator+=(float pret) {
		this->nrComponente++;
		float* aux = new float[this->nrComponente];
		for (int i = 0; i < this->nrComponente - 1; i++) {
			aux[i] = this->preturi[i];
		}
		aux[this->nrComponente - 1] = pret;
		if (this->preturi != nullptr) {
			delete[]this->preturi;
		}
		this->preturi = aux;
		return *this;
	}

	Masina operator+(float pret) const {
		Masina temp = *this;//generare eroare in cascada
		float* aux = new float[temp.nrComponente + 1];
		for (int i = 0; i < temp.nrComponente; i++) {
			aux[i] = this->preturi[i];
		}
		aux[temp.nrComponente] = pret;
		if (temp.preturi != nullptr) {
			delete[]temp.preturi;
		}
		temp.preturi = aux;
		temp.nrComponente++;
		return temp;
	}
	//masina2 = 3000.0f + masina3;
	//masina2=masina1+masina3;



	int getNrComponente() {
		return this->nrComponente;
	}



	void setNrComponente(int nrComponente) {
		if (nrComponente > 0) {
			this->nrComponente = nrComponente;
		}
		else {
			//throw "Valoare negativa!";
			//throw 400;
			throw new exception();
		}
	}

	//get si set pentru vectorul de preturi
	float* getPreturi() const {
		//return this->preturi;
		float* vectorPreturi = new float[this->nrComponente];
		for (int i = 0; i < this->nrComponente; i++) {
			vectorPreturi[i] = this->preturi[i];
		}
		return vectorPreturi;
	}

	void setPreturi(float* noulVectorPreturi, int nouaDimensiune) {
		setNrComponente(nouaDimensiune);
		if (this->preturi != nullptr) {
			delete[] this->preturi;
		}
		this->preturi = new float[nouaDimensiune];
		for (int i = 0; i < nouaDimensiune; i++) {
			this->preturi[i] = noulVectorPreturi[i];
		}
		delete[] noulVectorPreturi;
	}

	const int getId()const {
		return this->id;
	}
	friend Masina operator+(float pret, Masina m);

	~Masina() {
		//cout << endl << "S-a apelat destructorul!";
		if (this->preturi != nullptr)
			delete[] this->preturi;
	}

	void afisareMasina() {
		cout << this->id << ". Masina cu marca " << this->marca;
		if (this->nrComponente > 0) {
			cout << " are " << this->nrComponente << " componente cu urmatoarele preturi:";
			if (this->preturi != nullptr) {
				for (int i = 0; i < this->nrComponente; i++) {
					cout << " " << this->preturi[i];
				}
			}
		}
		cout << endl;
	}

	static int getNrMasini() {
		return nrMasini;
	}
	static void setNrMasini(int _nrMasini) {
		nrMasini = _nrMasini;
	}

};
int Masina::nrMasini = 0;


Masina operator+(float pret, Masina m) {
	Masina temp = m + pret;
	return temp;
}


int main() {

	Masina masina1("Dacia", 3, new float[3] {3, 5, 7});

	Masina masina2 = masina1;
	Masina masina3("BMW", 3, new float[3] {664, 645, 32});
	//masina3 = masina1;//masina3.operator=(masina1);
	//masina2 = masina3 = masina1;

	masina3 += 1000;
	masina2 = masina3 + 2000;

	masina2 = 3000 + masina3;

	masina2.afisareMasina();
}