#include<iostream>
#include<vector>
#include<string>

using namespace std;

class Animal{
    protected:
        string name;
        int age;
    public:
        Animal(const string& name, int age): name(name), age(age){}
        virtual void makeSound() const = 0;
        virtual void displayInfo() const{
            cout << "Name: " << name <<", Age: " << age<<  endl;
        }
        string getName() const { return name; }
        virtual ~Animal(){}
};

class Dogs: public Animal{
    private:
        string breed;
    public:
        Dogs(const string& name, int age, const string& breed)
            : Animal(name, age), breed(breed){}
        void makeSound() const override{
            cout << name << " says: Woof Woof!" << endl;
        }
        void displayInfo() const override{
            Animal::displayInfo();
            cout << "Breed: " << breed << endl;
        }
};

class Cats: public Animal{
    private:
        string color;
    public:
        Cats(const string& name, int age, const string& color)
            : Animal(name, age), color(color){}
        void makeSound() const override{
            cout << name << " says: Meow Meow!" << endl;
        }
        void displayInfo() const override{
            Animal::displayInfo(); // Sửa lỗi chính tả từ "Aniaml" thành "Animal"
            cout << "Color: " << color << endl;
        }
};

// class Kennel{
//     private:
//         vector<Animal*> animals; 
//     public:
//         // Thêm động vật vào danh sách
//         void addAnimal(Animal* animal) {
//             animals.push_back(animal);
//         }

//         // Xóa động vật khỏi danh sách theo tên
//         void removeAnimal(const string& name) {
//             for (auto it = animals.begin(); it != animals.end(); ++it) {
//                 if ((*it)->name == name) { // So sánh tên
//                     delete *it; // Giải phóng bộ nhớ
//                     animals.erase(it); // Xóa khỏi danh sách
//                     cout << "Animal with name " << name << " has been removed." << endl;
//                     return;
//                 }
//             }
//             cout << "Animal with name " << name << " not found." << endl;
//         }

//         // Liệt kê tất cả động vật trong danh sách
//         void listAnimals() const {
//             for (const auto& animal : animals) {
//                 animal->displayInfo();
//                 animal->makeSound();
//                 cout << "-----------------" << endl;
//             }
//         }

//         // Destructor để giải phóng bộ nhớ
//         ~Kennel() {
//             for (auto& animal : animals) {
//                 delete animal;
//             }
//         }
// };

class Kennel {
private:
    Animal** animals; // Mảng con trỏ động vật
    int maxAnimals;   // Số lượng tối đa động vật
    int currentCount; // Số lượng động vật hiện tại

public:
    Kennel(int maxAnimals) : maxAnimals(maxAnimals), currentCount(0) {
        animals = new Animal*[maxAnimals];
        for (int i = 0; i < maxAnimals; i++) {
            animals[i] = nullptr;
        }
    }

    // Thêm động vật vào Kennel, trả về vị trí hoặc -1 nếu đầy
    int addAnimal(Animal* animal) {
        if (currentCount >= maxAnimals) {
            cout << "Kennel is full!" << endl;
            return -1;
        }
        for (int i = 0; i < maxAnimals; i++) {
            if (animals[i] == nullptr) {
                animals[i] = animal;
                currentCount++;
                cout << "Added animal at position " << i << endl;
                return i;
            }
        }
        return -1; // Không thể xảy ra
    }

    // Xóa động vật khỏi Kennel theo tên
    void removeAnimal(const string& name) {
        for (int i = 0; i < maxAnimals; i++) {
            if (animals[i] != nullptr && animals[i]->getName() == name) {
                delete animals[i];
                animals[i] = nullptr;
                currentCount--;
                cout << "Removed animal with name " << name << " from position " << i << endl;
                return;
            }
        }
        cout << "Animal with name " << name << " not found." << endl;
    }

    // Liệt kê tất cả động vật trong Kennel
    void listAnimals() const {
        for (int i = 0; i < maxAnimals; i++) {
            if (animals[i] != nullptr) {
                cout << "Position " << i << ": ";
                animals[i]->displayInfo();
                animals[i]->makeSound();
            }
        }
    }

    // Destructor để giải phóng bộ nhớ
    ~Kennel() {
        for (int i = 0; i < maxAnimals; i++) {
            delete animals[i];
        }
        delete[] animals;
    }
};

int main() {
    Kennel kennel(5); 

    kennel.addAnimal(new Dogs("Buddy", 3, "Golden Retriever"));
    kennel.addAnimal(new Cats("Whiskers", 2, "White"));
    kennel.addAnimal(new Dogs("Max", 4, "Bulldog"));

    cout << "\nAnimals in the kennel:" << endl;
    kennel.listAnimals();

    cout << "\nRemoving 'Buddy' from the kennel..." << endl;
    kennel.removeAnimal("Buddy");

    cout << "\nAnimals in the kennel after removal:" << endl;
    kennel.listAnimals();

    cout << "\nAdding a new animal..." << endl;
    kennel.addAnimal(new Cats("Mittens", 1, "Black"));

    cout << "\nAnimals in the kennel after adding a new one:" << endl;
    kennel.listAnimals();

    return 0;
}
// int main() {
//     Kennel kennel;

//     kennel.addAnimal(new Dogs("Buddy", 3, "Golden Retriever"));
//     kennel.addAnimal(new Cats("Whiskers", 2, "White"));

//     cout << "Animals in the kennel:" << endl;
//     kennel.listAnimals();

//     cout << "Removing 'Buddy' from the kennel..." << endl;
//     kennel.removeAnimal("Buddy");

//     cout << "Animals in the kennel after removal:" << endl;
//     kennel.listAnimals();

//     return 0;
// }