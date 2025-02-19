#include <iostream>
#include <cstdint>
#include <cctype>
#include <string>
#include <vector>
using namespace std;

class Policy {

protected:
    bool isChecked;

public:
    virtual void check(const std:: string &password) = 0;

    bool getCheck() const {return isChecked;}

    /* void again() {isChecked = false;}*/

};


class LengthPolicy: public Policy {

private:
    uint16_t minLength,maxLength;

public:
    explicit LengthPolicy(uint16_t min) : minLength(min), maxLength(255) {}
    LengthPolicy(uint16_t min,uint16_t max) : minLength(min), maxLength(max) {}

    void check(const std::string& password) override {
        if (minLength > 0 && minLength <= maxLength && password.length() >= minLength && password.length() <= maxLength ) {
            isChecked = true;
        } else {
            isChecked = false;
        }
    }

};


class classPolicy: public Policy {

private:
    uint16_t minClassCount;

public:
    explicit classPolicy(uint16_t minClassCount) : minClassCount(minClassCount) {}

    void check(const std::string& password) override {

        int contor1 = 0;
        int contor2 = 0;
        int contor3 = 0;
        int contor4 = 0;


        if (minClassCount > 0 && minClassCount < 5 ) {

            for (int i = 0 ; i < password.length() ; i++) {

                if ( islower(password[i])  ) {
                    contor1 = 1;

                }

                if ( isupper(password[i])  ) {
                    contor2 = 1;

                }

                if ( isdigit(password[i])  ) {
                    contor3 = 1;

                }

                if ( ispunct(password[i])  ) {
                    contor4 = 1;

                }

            }

            if ( (contor1 + contor2 + contor3 + contor4) >= minClassCount ) {
                isChecked = true;
            } else { isChecked = false; }

        }
    }

};


class IncludePolicy: public Policy {

private:
    char characterType;

public:
    explicit IncludePolicy(char character) : characterType(character) {}

    void check(const std::string& password) override {


        if (characterType == 'a') {
            for (int i = 0; i < password.length(); i++) {
                if (islower(password[i])) {
                    isChecked = true;
                    break;
                }  else {
                    isChecked = false;
                }
            }
        } else if (characterType == 'A') {
            for (int i = 0; i < password.length(); i++) {
                if (isupper(password[i])) {
                    isChecked = true;
                    break;
                }  else {
                    isChecked = false;
                }
            }
        } else if (characterType == '0') {
            for (int i = 0; i < password.length(); i++) {
                if (isdigit(password[i])) {
                    isChecked = true;
                    break;
                }  else {
                    isChecked = false;
                }
            }
        } else if (characterType == '$') {
            for (int i = 0; i < password.length(); i++) {
                if (ispunct(password[i])) {
                    isChecked = true;
                    break;
                }  else {
                    isChecked = false;
                }
            }
        }


    }

};


class NotIncludePolicy: public Policy {

private:
    char characterType;

public:
    explicit NotIncludePolicy(char character) : characterType(character) {}

    void check(const std::string& password) override {

        if (characterType == 'a') {
            for (int i = 0; i < password.length(); i++) {
                if (islower(password[i])) {
                    isChecked = false;
                    break;
                }
                else {
                    isChecked = true;
                }
            }
        } else if (characterType == 'A') {
            for (int i = 0; i < password.length(); i++) {
                if (isupper(password[i])) {
                    isChecked = false;
                    break;
                }
                else {
                    isChecked = true;
                }
            }
        } else if (characterType == '0') {
            for (int i = 0; i < password.length(); i++) {
                if (isdigit(password[i])) {
                    isChecked = false;
                    break;
                }
                else {
                    isChecked = true;
                }
            }
        } else if (characterType == '$') {
            for (int i = 0; i < password.length(); i++) {
                if (ispunct(password[i])) {
                    isChecked = false;
                    break;
                }
                else {
                    isChecked = true;
                }
            }
        }


    }

};



class RepetitionPolicy: public Policy {

private:
    uint16_t maxCount;

public:
    explicit RepetitionPolicy(uint16_t max) : maxCount(max) {}

    void check(const std::string& password) override {
        int contor = 1;
        isChecked = true;

        if (maxCount > 0) {
            for (int i = 0; i < password.length() - 1; i++) {
                if (password[i] == password[i + 1]) {
                    contor++;
                    if (contor > maxCount) {
                        isChecked = false;
                        break;
                    }
                } else {
                    contor = 1;
                }
            }
        }
    }


    /*void check(const std::string& password) override {

        int contor = 1 ;
        int a = 1;

        if ( maxCount > 0 ) {

            for (int i = 0; i < password.length() - 1; i++) {

                if (password[i] == password[i + 1]) {
                    contor++;

                } else a = 0;

                if (a == 0 && contor <= maxCount) {
                    isChecked = true;
                    contor = 1;
                } else {
                    isChecked = false;
                    break;
                }
            }
        }



    }*/

};


class ConsecutivePolicy: public Policy {

private:
    uint16_t maxCount;

public:
    explicit ConsecutivePolicy(uint16_t max) : maxCount(max) {}

    void check(const std::string& password) override {

        int contor = 1;
        int a = 1;

        for ( int i = 0 ; i < password.length() - 1 ; i++) {

            if (password[i+1] - password[i] == 1) {
                contor++ ;

            } else a = 0;

            if (a == 0 && contor <= maxCount) {
                isChecked = true;
                contor = 1;
            } else {
                isChecked = false;
                break;
            }
        }



    }

};


std::string checkPassword(std::string &password, std:: vector <Policy*> policies ) {

    int contor = 0;


    for (int i = 0; i < policies.size(); i++) {

        /* policies[i]->again();*/
        policies[i]->check(password);
        if (policies[i]->getCheck()) contor++;

    }

    if (contor == policies.size()) return "OK";
    return "NOK";

}


int main () {

    std::string  pol;
    std::string password;
    char c;
    uint16_t min,max;

    long int n;
    scanf("%ld", &n);

    std:: vector <Policy*> policies;

    for ( int i = 0 ; i < n ; i++ ) {

        cin>> pol;

        if ( pol == "length" ) {
            scanf("%hu", &min);
/// !!!!!!!!!
            if ( (scanf("%hu", &max) != 0  ) ) {
                policies.push_back(new LengthPolicy(min,max));
            } else {
                policies.push_back(new LengthPolicy(min));
            }
        }

        if (pol == "class") {
            scanf("%hu", &min);
            policies.push_back(new  classPolicy(min));

        }

        if ( pol == "include") {
            scanf(" %c", &c);
            policies.push_back(new IncludePolicy(c));
        }

        if ( pol == "ninclude") {
            scanf(" %c", &c);
            policies.push_back(new NotIncludePolicy(c));
        }

        if ( pol == "repetition") {
            scanf("%hu", &max);
            policies.push_back(new RepetitionPolicy(max));
        }

        if (pol == "consecutive") {
            scanf("%hu", &max);
            policies.push_back(new ConsecutivePolicy(max));
            /*  ConsecutivePolicy* p = new ConsecutivePolicy(max);
              policies.push_back(p);  */
        }

    }

/*!!!!!!*/
    while ( cin>>password )  {
        std::cout <<  checkPassword(password,policies) << std::endl;
    }


    return 0;
}