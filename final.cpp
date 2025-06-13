#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class Account {
	Account* ptr;
    string name;
    int ID;
    
public:
    // �غc�l
    Account() : ID(0){}
    Account(int ID, string name) : ID(ID), name(name) {}
    virtual ~Account() {}

    // ��Ʀs���禡
    void set_name(string s) { name = s; }
    void set_ID(int n) { ID = n; }
    
    int get_ID() { return ID; }
    string get_name() { return name; }
    
    void set_ptr(Account* p) { ptr = p; }
    Account* get_ptr() { return ptr; }
};

class TW_Account: public Account{
	int rest;
	int total_borrow;

public:
	TW_Account(int ID = 0, string name = "", int rest = 0, int total_borrow = 0): rest(rest), total_borrow(total_borrow), Account(ID, name) {}
	// �B��l����
    void operator+(int x) { rest += x; }
    void operator-(int y) { rest -= y; }
    void operator+=(int a){total_borrow += a;}
    void operator-=(int b){total_borrow -= b;}
    
    
	void set_rest(int a) { rest = a; }
    void set_total_borrow(int b) { total_borrow = b; }
    
    int get_rest() { return rest; }
    int get_total_borrow() { return total_borrow; }
    
    //int get_total() { return (run + swim + AI); }

};

class JP_Account: public Account{
	int rest;
	int total_borrow;
	
public:
	JP_Account(int ID = 0, string name = "", int rest = 0, int total_borrow = 0): rest(rest), total_borrow(total_borrow), Account(ID, name) {}
	void operator+(int x) { rest += x; }
    void operator-(int y) { rest -= y; }
    void operator+=(int a){total_borrow += a;}
    void operator-=(int b){total_borrow -= b;}
    //void operator+(int x) { prg += x; ing += x; }
	
	void set_rest(int a) { rest = a; }
    void set_total_borrow(int b) { total_borrow = b; }
    int get_rest() { return rest; }
    int get_total_borrow() { return total_borrow; }
    //int get_total() { return (prg + ing); }
    // �R�A��ƾާ@
    
};

class Bank {
    int select;
    double rest_money;
    Account* TW_head;
    Account* JP_head;
public:
	void set_rest_money(double r) { rest_money = r; }
	double get_rest_money() { return rest_money; }
    void operator+(double x) { rest_money += x; }
    void operator-(double x) { rest_money -= x; }
    
    void set_TW_head(Account* p) { TW_head = p; }
    void set_JP_head(Account* p) { JP_head = p; }
    Account* get_TW_head() { return TW_head; }
    Account* get_JP_head() { return JP_head; }
    
    Bank() : select(1), rest_money(0.00), TW_head(NULL), JP_head(NULL) {}

    void w_select(int x) { select = x; }
    int r_select() { return select; }
    void show() {
        cout << "\n���" << endl;
        cout << "1. �s�W�b����" << endl;
        cout << "2. �d�߱b����" << endl;
        cout << "3. �Τ�s�B����" << endl;
        cout << "4. �Τ�ɡB�ٿ�" << endl;
        cout << "5. ��ܻȦ�l�B" << endl;
        cout << "6. ��ܩҦ���Ʀܿù�" << endl;
        cout << "7. �C�L�Ҧ���Ʀ��ɮ�" << endl;
        cout << "0. ���}" << endl;
        cout << "�п�J��ܶ��ءH";
    }
};

// �s�W
void add(Bank& Bank) {
    Account* p = NULL;
    int ID, country;
    bool valid = false;
    ofstream output("output.txt", ios::app);

    cout << "�п�J�b����ơG" << endl;
    cout << "�п�ܱb������(1�GTW�A2�GJP)" << endl;
    cin >> country;
    cin.ignore();

    if (country == 1) {
        p = new TW_Account;
        ID  = 10001;
        Account *temp = Bank.get_TW_head(); 
        while (!valid) {
            valid = true;
            temp = Bank.get_TW_head();
            while (temp != NULL) {
                if (temp->get_ID() == ID) {
                    //cout << "���~�G�b���w�g�s�b�A�Э��s��J�I" << endl;
                    ID+=1;
                    valid = false;
                    break;
                }
                temp = temp->get_ptr();
            }
        }

        p->set_ID(ID);

        cout << "�m�W�G";
        string name;
        getline(cin, name);
        p->set_name(name);
        
        cout << "��l���B�G";
        int initial_money;
        cin >> initial_money;
        if(initial_money < 0){
		cout << "���i���t��" << endl;
		return;}
        dynamic_cast<TW_Account*>(p)->set_rest(initial_money);
        Bank + initial_money;
        
        //if (output.is_open()) {
            //output << "1," << no << "," << name << ","
                   //<< r << "," << s << "," << a << endl;
        //}
        
        
    } else if (country == 2) {
        p = new JP_Account;
        ID = 20001;
        Account* temp = Bank.get_JP_head();
        while (!valid) {
            valid = true;
            temp = Bank.get_JP_head();
            while (temp != NULL) {
                if (temp->get_ID() == ID) {
                    ID+=1;
                    valid = false;
                    break;
                }
                temp = temp->get_ptr();
            }
        }

        p->set_ID(ID);

        cout << "�m�W�G";
        string name;
        getline(cin, name);
        p->set_name(name);
        
        cout << "��l���B�G";
        int initial_money;
        cin >> initial_money;
        if(initial_money < 0){
		cout << "���i���t��" << endl;
		return;}
        dynamic_cast<JP_Account*>(p)->set_rest(initial_money);
        Bank + (initial_money*0.2); 
        
        //if (output.is_open()) {
            //output << "2," << no << "," << name << ","
       		//<< prg << "," << ing << endl;
        //}

    } else {
        cout << "�L���b�������I" << endl;
        return;
    }
	
    // ���J�s�`�I
	Account* head = (country == 1) ? Bank.get_TW_head() : Bank.get_JP_head();
	if (head == NULL || head->get_ID() > ID) {
	    p->set_ptr(head);
	    if (country == 1)
	        Bank.set_TW_head(p);  
	    else
	        Bank.set_JP_head(p); 
	} else {
	    Account* prev = head;
	    Account* curr = head->get_ptr();
	    while (curr != NULL && curr->get_ID() < ID) {
	        prev = curr;
	        curr = curr->get_ptr();
	    }
	    prev->set_ptr(p);
	    p->set_ptr(curr);
	}

    cout << "�w�s�W�����I" << endl;
     output.close();
}

// �d��
void search(Bank& Bank) {

    cout << "��J�n�d�ߪ��b���m�W�G";
    bool check_TW = false;
    bool check_JP = false;
    string name;
    cin.ignore();  
    getline(cin, name);

    Account* p = Bank.get_TW_head();

    while (p != NULL) {
        if (p->get_name() == name) {
    
            TW_Account* peStudent = dynamic_cast<TW_Account*>(p);
                if (peStudent) {
                	cout << "ID: " << p->get_ID() << endl;
            		cout << "�m�W: " << p->get_name() << endl;
                    cout << "�l�B: " << peStudent->get_rest() << endl;
                    cout << "�ɿ��`��: " << peStudent->get_total_borrow() << endl;
                }
                check_TW = true;
        }
        p = p->get_ptr();  // ����U�@�Ӹ`�I
    }
    
    if (!check_TW) {
        cout << "TW Account���L�ŦX���" << endl;  
    }
    
    p = Bank.get_JP_head();
    while (p != NULL) {
        if (p->get_name() == name) {
    
            JP_Account* peStudent = dynamic_cast<JP_Account*>(p);
                if (peStudent) {
                	cout << "ID: " << p->get_ID() << endl;
            		cout << "�m�W: " << p->get_name() << endl;
                    cout << "�l�B: " << peStudent->get_rest() << endl;
                    cout << "�ɿ��`��: " << peStudent->get_total_borrow() << endl;
                }
                check_JP = true;
        }
        p = p->get_ptr();  // ����U�@�Ӹ`�I
    }

    if (!check_JP) {
        cout << "JP Account���L�ŦX���" << endl;  
    }
}

//�s���� 
void SaveTake(Bank& Bank) {
	cout << "��J�ϥΪ�ID�G" << endl; 
    string ID;
    cin >> ID;
    
    int int_ID = atoi(ID.c_str());

    Account* p = (ID[0] == '1') ? Bank.get_TW_head() : Bank.get_JP_head();
    
    while (p != NULL) {
        if (p->get_ID() == int_ID) {
        	cout << "�п�ܦs���Ψ���(1: �s�� 2. ����)�G";
    		int option;
    		cin >> option;
    		
    		cout << "�Ȧ�l�B���G" << fixed << setprecision(2) << Bank.get_rest_money() << endl;

        	cout << "�п�J���B�G"<< endl; 
            int x ;
            cin >> x; 
            if(x < 0){
				cout << "���i���t��" << endl;
				return;}

            if (ID[0] == '1') {
                // TW_Account
                TW_Account* peStudent = dynamic_cast<TW_Account*>(p);
                if (peStudent) {
                	if(option==1){
                		peStudent->set_rest(peStudent->get_rest() + x);
                		Bank + x;
                		cout << "�l�B�w��s���G" << peStudent->get_rest() << endl;
					}
					if(option==2){
                		//�ϥΪ̾l�B���p������q 
                		if(peStudent->get_rest() < x){
                			cout << "�l�B�����I�G" << endl; 
                		//�Ȧ�Ѿl�������p������q 
						}else if(Bank.get_rest_money() < x){
						cout << "�Ȧ�Ѿl���������I" << endl; 
						} else{
						peStudent->set_rest(peStudent->get_rest() - x);
						Bank - x;
						cout << "�l�B�w��s���G" << peStudent->get_rest() << endl;}
					}
                } 
            } else {
                JP_Account* peStudent = dynamic_cast<JP_Account*>(p);
                if (peStudent) {
                	if(option==1){
                		peStudent->set_rest(peStudent->get_rest() + x);
                		Bank + (x*0.2);
                		cout << "�l�B�w��s���G" << peStudent->get_rest() << endl;
					}
					if(option==2){
                		//�ϥΪ̾l�B���p������q 
                		if(peStudent->get_rest() < x){
                			cout << "�l�B�����I�G" << endl; 
                		//�Ȧ�Ѿl�������p������q 
						}else if(Bank.get_rest_money() < (x*0.2)){
						cout << "�Ȧ�Ѿl���������I" << endl;  
						} else{
						peStudent->set_rest(peStudent->get_rest() - x);
						Bank - (x*0.2);
						cout << "�l�B�w��s���G" << peStudent->get_rest() << endl;
						}
                	} 
            	}
        	}
        return;
    	}
        p = p->get_ptr();
    }
    cout << "�d�L���b���I" << endl;
}

// ���ٿ� 
void BorrowLent(Bank& Bank) {
	cout << "��J�ϥΪ�ID�G" << endl; 
    string ID;
    cin >> ID;
    
    int int_ID=atoi(ID.c_str());

    Account* p = (ID[0] == '1') ? Bank.get_TW_head() : Bank.get_JP_head();
    
    while (p != NULL) {
        if (p->get_ID() == int_ID) {
        	cout << "�п�ܭɿ����ٿ�(1: �ɿ� 2. �ٿ�)�G";
    		int option;
    		cin >> option;
    		
    		cout << "�Ȧ�l�B���G" << fixed << setprecision(2) << Bank.get_rest_money() << endl;

    		
        	cout << "�п�J���B�G"<< endl; 
            int x ;
            cin >> x; 
            if(x < 0){
				cout << "���i���t��" << endl;
				return;}

            if (ID[0] == '1') {
                // TW_Account
                TW_Account* peStudent = dynamic_cast<TW_Account*>(p);
                if (peStudent) {
                	if(option==1){
                		if(Bank.get_rest_money() < x){
                			cout << "�Ȧ�Ѿl���������I" << endl;
						}else{
							peStudent->set_total_borrow(peStudent->get_total_borrow() + x);
							Bank - x;
							cout << "�ɿ��`�B�w��s���G" << peStudent->get_total_borrow() << endl;
						}
					}
					if(option==2){
						if(x > peStudent->get_total_borrow()){
							cout << "�ٿ����B�j��ɿ��q�I" << endl;
						}else{
							peStudent->set_total_borrow(peStudent->get_total_borrow() - x);
							Bank + x;
							cout << "�ɿ��`�B�w��s���G" << peStudent->get_total_borrow() << endl;
						}
					}
           	 	}
			 }else {
                JP_Account* peStudent = dynamic_cast<JP_Account*>(p);
                if (peStudent) {
                	if(option==1){
                		if(Bank.get_rest_money() < (x*0.2)){
                			cout << "�Ȧ�Ѿl���������I" << endl;
						}else{
							peStudent->set_total_borrow(peStudent->get_total_borrow() + x);
							Bank - (x*0.2); 
							cout << "�ɿ��`�B�w��s���G" << peStudent->get_total_borrow() << endl;
						}
					}
					if(option==2){
						if(x > peStudent->get_total_borrow()){
							cout << "�ٿ����B�j��ɿ��q�I" << endl;
						}else{
							peStudent->set_total_borrow(peStudent->get_total_borrow() - x);
							Bank + (x*0.2);
							cout << "�ɿ��`�B�w��s���G" << peStudent->get_total_borrow() << endl;
						}
					}
                } 
            }
			return;
        }
        p = p->get_ptr();
    }

    cout << "�d�L���b���I" << endl;
}

//�Ȧ�l�B
void bankShow(Bank& Bank){
	cout << "�Ȧ�l�B���G" << fixed << setprecision(2) << Bank.get_rest_money() << endl;
} 

// ��� 
void DataShow(Bank& Bank) {
    Account* p = Bank.get_TW_head();
    if (p == NULL) {
        cout << "�ثe�S������TW�b���ơC" << endl;
    } else {
        // �L�X TW �b����
        cout << "TW�b���ơG" << endl;
        cout << left
             << setw(8)  << "ID"
             << setw(10) << "�m�W"
             << setw(12) << "�l�B"
             << setw(12) << "�ɿ��`�B" << endl;

        while (p != NULL) {
            TW_Account* tw = static_cast<TW_Account*>(p);
            cout << setw(8)  << tw->get_ID()
                 << setw(10) << tw->get_name()
                 << setw(12) << tw->get_rest()
                 << setw(12) << tw->get_total_borrow() << endl;
            p = p->get_ptr();
        }
    }

    p = Bank.get_JP_head();
    if (p == NULL) {
        cout << "�ثe�S������JP�b���ơC" << endl;
    } else {
        // �L�X JP �b����
        cout << "JP�b���ơG" << endl;
        cout << left
             << setw(8)  << "ID"
             << setw(10) << "�m�W"
             << setw(12) << "�l�B"
             << setw(12) << "�ɿ��`�B" << endl;

        while (p != NULL) {
            JP_Account* jp = static_cast<JP_Account*>(p);
            cout << setw(8)  << jp->get_ID()
                 << setw(10) << jp->get_name()
                 << setw(12) << jp->get_rest()
                 << setw(12) << jp->get_total_borrow() << endl;
            p = p->get_ptr();
        }
    }

    // �Τ@�����T��
    cout << "�w��ܡI" << endl;
}


void print(Bank& Bank) {
	ofstream fout("output.txt");  // �s�W��X�ɮ�
    if (!fout) {
        cout << "�L�k�}���ɮ� output.txt�I" << endl;
        return;
    }
    
    Account* p = Bank.get_TW_head();
    if (p == NULL) {
        fout << "�ثe�S������TW�b���ơC" << endl;
        cout << "�ثe�S������TW�b���ơC" << endl;
    }else{
	// �L�X���D�C
	cout << "TW�b���ơG" << endl;
	fout << "TW�b���ơG" << endl;
	cout << left
         << setw(8)  << "ID"
         << setw(10) << "�m�W"
         << setw(12) << "�l�B"
         << setw(12) << "�ɿ��`�B" << endl;
	
    fout << left
         << setw(8)  << "ID"
         << setw(10) << "�m�W"
         << setw(12) << "�l�B"
         << setw(12) << "�ɿ��`�B" << endl;
      
    while (p != NULL) {
        // �L�X�򥻸��
        TW_Account* tw = static_cast<TW_Account*>(p);
        cout << setw(8)  << tw->get_ID()
             << setw(10) << tw->get_name()
             << setw(12) << tw->get_rest()
             << setw(12) << tw->get_total_borrow() << endl;
        
        fout << setw(8)  << tw->get_ID()
             << setw(10) << tw->get_name()
             << setw(12) << tw->get_rest()
             << setw(12) << tw->get_total_borrow() << endl;
             p = p->get_ptr();
    }	
	}
    p = Bank.get_JP_head();
    if (p == NULL) {
    	cout << "�ثe�S������JP�b���ơC" << endl;
        fout << "�ثe�S������JP�b���ơC" << endl;
    }else{
    	cout << "JP�b���ơG" << endl;
		fout << "JP�b���ơG" << endl;
    	cout << left
         << setw(8)  << "ID"
         << setw(10) << "�m�W"
         << setw(12) << "�l�B"
         << setw(12) << "�ɿ��`�B" << endl;
    	
    	fout << left
         << setw(8)  << "ID"
         << setw(10) << "�m�W"
         << setw(12) << "�l�B"
         << setw(12) << "�ɿ��`�B" << endl;
		      
    while (p != NULL) {
        // �L�X�򥻸��
        JP_Account* jp = static_cast<JP_Account*>(p);
        cout << setw(8)  << jp->get_ID()
             << setw(10) << jp->get_name()
             << setw(12) << jp->get_rest()
             << setw(12) << jp->get_total_borrow() << endl;
        
        fout << setw(8)  << jp->get_ID()
             << setw(10) << jp->get_name()
             << setw(12) << jp->get_rest()
             << setw(12) << jp->get_total_borrow() << endl;
             p = p->get_ptr();
    }
	}
    fout.close();
    cout << "�w�C�L�I" << endl;
    //input.close();
}

//�s��� 
void save(Bank& bank) {
    ofstream fout("data.txt");
    if (!fout) {
        cout << "�ɮ׶}�ҥ��ѡI" << endl;
        return;
    }
    
    // �sTW�b��
    Account* p = bank.get_TW_head();
    while (p != NULL) {
        TW_Account* tw = dynamic_cast<TW_Account*>(p);
        if (tw) {
            fout << 1 << "," << tw->get_ID() << "," << tw->get_name() << ","
                 << tw->get_rest() << "," << tw->get_total_borrow() << "\n";
        }
        p = p->get_ptr();
    }
    
    // �sJP�b��
    p = bank.get_JP_head();
    while (p != NULL) {
        JP_Account* jp = dynamic_cast<JP_Account*>(p);
        if (jp) {
            fout << 2 << "," << jp->get_ID() << "," << jp->get_name() << ","
                 << jp->get_rest() << "," << jp->get_total_borrow() << "\n";
        }
        p = p->get_ptr();
    }
    
    fout.close();
    cout << "��Ƥw�s�ɦ�data.txt" << endl;
}

//���J���
void load(Bank& Bank) {
    ifstream fin("data.txt");
    if (!fin) {
        ofstream fout("data.txt", ios::app);
        return;
    }
    
    Bank.set_TW_head(NULL);
    Bank.set_JP_head(NULL);

    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        string token;
        
        int type, ID, rest, total_borrow;
        string name;
        
        // Ū���b������
        getline(ss, token, ',');
        type = atoi(token.c_str());

        // ŪID
        getline(ss, token, ',');
        ID = atoi(token.c_str());

        // Ū�m�W
        getline(ss, name, ',');

        // Ū�l�B
        getline(ss, token, ',');
        rest = atoi(token.c_str());

        // Ū�ɴ��`�B
        getline(ss, token, ',');
        total_borrow = atoi(token.c_str());

        Account* p = NULL;
        if (type == 1) {
            p = new TW_Account(ID, name, rest, total_borrow);
            // ���JTW��C(�Ѥp��jID)
            Account* head = Bank.get_TW_head();
            if (head == NULL || head->get_ID() > ID) {
                p->set_ptr(head);
                Bank.set_TW_head(p);
            } else {
                Account* prev = head;
                Account* curr = head->get_ptr();
                while (curr != NULL && curr->get_ID() < ID) {
                    prev = curr;
                    curr = curr->get_ptr();
                }
                prev->set_ptr(p);
                p->set_ptr(curr);
            }
        } else if (type == 2) {
            p = new JP_Account(ID, name, rest, total_borrow);
            // ���JJP��C(�Ѥp��jID)
            Account* head = Bank.get_JP_head();
            if (head == NULL || head->get_ID() > ID) {
                p->set_ptr(head);
                Bank.set_JP_head(p);
            } else {
                Account* prev = head;
                Account* curr = head->get_ptr();
                while (curr != NULL && curr->get_ID() < ID) {
                    prev = curr;
                    curr = curr->get_ptr();
                }
                prev->set_ptr(p);
                p->set_ptr(curr);
            }
        }
    }
    
    fin.close();
    cout << "��Ƥw�qdata.txt���J" << endl;
}

int main() {
	Bank menu;
	
    load(menu);
    string line;

    do {
        int s;
        menu.show();
        cin >> s;
        menu.w_select(s);
        switch (menu.r_select()) {
        case 0: {
        	save(menu);
            cout << "�w�h�X" << endl;
            break;
        }
        case 1: {
            add(menu);
            break;
        }
        case 2: {
            search(menu);
            break;
        }
        case 3: {
            SaveTake(menu);
            break;
        }
        case 4: {
            BorrowLent(menu);
            break;
        }
		case 5: {
            bankShow(menu);
            break;
        }
        case 6: {
            DataShow(menu);
            break;
        }
        case 7: {
            print(menu);
            break;
        }
        default:
            cout << "�L�Ŀﶵ�A�Э��s��J�I" << endl;
        }
        
    } while (menu.r_select() != 0);
    
    

    return 0;
}


