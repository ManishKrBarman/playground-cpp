#include <iostream>
#include <string>

// Class demonstrating all visibility levels
class VisibilityDemo {
private:
    int privateData = 10;           // Only accessible within this class
    void privateMethod() {
        std::cout << "Private method called" << std::endl;
    }

protected:
    int protectedData = 20;         // Accessible by this class and derived classes
    void protectedMethod() {
        std::cout << "Protected method called" << std::endl;
    }

public:
    int publicData = 30;            // Accessible by everyone
    void publicMethod() {
        std::cout << "Public method called" << std::endl;
        // Can access all members within the same class
        privateData = 40;
        privateMethod();
        protectedData = 50;
        protectedMethod();
    }
    
    // Constructor to demonstrate access
    VisibilityDemo() {
        std::cout << "VisibilityDemo constructor" << std::endl;
        std::cout << "Private data: " << privateData << std::endl;
        std::cout << "Protected data: " << protectedData << std::endl;
        std::cout << "Public data: " << publicData << std::endl;
    }
    
    // Public method to access private members (controlled access)
    int getPrivateData() const {
        return privateData;
    }
    
    void setPrivateData(int value) {
        if (value >= 0) {  // Validation in setter
            privateData = value;
        }
    }
};

// Derived class to demonstrate inheritance access
class DerivedDemo : public VisibilityDemo {
public:
    void demonstrateAccess() {
        std::cout << "\n--- Access from Derived Class ---" << std::endl;
        
        // Can access public members
        publicData = 100;
        publicMethod();
        
        // Can access protected members
        protectedData = 200;
        protectedMethod();
        
        // Cannot access private members
        // privateData = 300;     // ERROR: private member not accessible
        // privateMethod();       // ERROR: private method not accessible
        
        // Must use public interface to access private data
        setPrivateData(300);
        std::cout << "Private data via getter: " << getPrivateData() << std::endl;
    }
};

// Friend function declaration (can access private members)
class FriendDemo {
private:
    int secret = 42;
    
public:
    // Friend function declaration
    friend void revealSecret(const FriendDemo& obj);
    
    // Friend class declaration
    friend class FriendClass;
    
    void publicFunction() {
        std::cout << "FriendDemo public function" << std::endl;
    }
};

// Friend function implementation (can access private members)
void revealSecret(const FriendDemo& obj) {
    std::cout << "Friend function accessing secret: " << obj.secret << std::endl;
}

// Friend class (can access all members of FriendDemo)
class FriendClass {
public:
    void accessFriend(const FriendDemo& obj) {
        std::cout << "Friend class accessing secret: " << obj.secret << std::endl;
    }
};

// Struct vs Class default visibility
struct StructDemo {
    int data;  // Public by default
    void method() { std::cout << "Struct method (public by default)" << std::endl; }
private:
    int privateData;  // Explicitly private
};

class ClassDemo {
    int data;  // Private by default
    void method() { std::cout << "Class method (private by default)" << std::endl; }
public:
    void publicMethod() { std::cout << "Class public method" << std::endl; }
};

// Access control with inheritance types
class Base {
public:
    int publicMember = 1;
protected:
    int protectedMember = 2;
private:
    int privateMember = 3;
};

// Public inheritance - most common
class PublicDerived : public Base {
public:
    void showAccess() {
        std::cout << "\n--- Public Inheritance ---" << std::endl;
        std::cout << "Public member: " << publicMember << std::endl;      // Remains public
        std::cout << "Protected member: " << protectedMember << std::endl;// Remains protected
        // privateMember not accessible
    }
};

// Protected inheritance - rarely used
class ProtectedDerived : protected Base {
public:
    void showAccess() {
        std::cout << "\n--- Protected Inheritance ---" << std::endl;
        std::cout << "Public member (now protected): " << publicMember << std::endl;
        std::cout << "Protected member: " << protectedMember << std::endl;
    }
};

// Private inheritance - "implemented-in-terms-of" relationship
class PrivateDerived : private Base {
public:
    void showAccess() {
        std::cout << "\n--- Private Inheritance ---" << std::endl;
        std::cout << "Public member (now private): " << publicMember << std::endl;
        std::cout << "Protected member (now private): " << protectedMember << std::endl;
    }
    
    // Can selectively expose base class members
    using Base::publicMember;  // Make publicMember public again
};

// Encapsulation example - proper data hiding
class BankAccount {
private:
    double balance;
    std::string accountNumber;
    
    // Private helper method
    bool isValidAmount(double amount) const {
        return amount > 0;
    }

public:
    BankAccount(const std::string& accNum, double initialBalance = 0.0)
        : accountNumber(accNum), balance(initialBalance) {
        if (initialBalance < 0) {
            balance = 0.0;
        }
    }
    
    // Controlled access to private data
    double getBalance() const {
        return balance;
    }
    
    std::string getAccountNumber() const {
        return accountNumber;
    }
    
    // Business logic with validation
    bool deposit(double amount) {
        if (isValidAmount(amount)) {
            balance += amount;
            return true;
        }
        return false;
    }
    
    bool withdraw(double amount) {
        if (isValidAmount(amount) && amount <= balance) {
            balance -= amount;
            return true;
        }
        return false;
    }
};

int main() {
    std::cout << "Visibility Demo:" << std::endl;
    
    // Basic visibility demonstration
    VisibilityDemo obj;
    
    // Can access public members directly
    obj.publicData = 60;
    obj.publicMethod();
    
    // Cannot access private or protected members directly
    // obj.privateData = 70;    // ERROR
    // obj.protectedData = 80;  // ERROR
    
    // Must use public interface for controlled access
    obj.setPrivateData(70);
    std::cout << "Private data: " << obj.getPrivateData() << std::endl;
    
    // Derived class access demonstration
    DerivedDemo derived;
    derived.demonstrateAccess();
    
    // Friend function demonstration
    std::cout << "\n--- Friend Access ---" << std::endl;
    FriendDemo friendObj;
    revealSecret(friendObj);  // Friend function can access private members
    
    FriendClass friendClass;
    friendClass.accessFriend(friendObj);
    
    // Struct vs Class default visibility
    std::cout << "\n--- Struct vs Class Defaults ---" << std::endl;
    StructDemo structObj;
    structObj.data = 100;  // Public by default
    structObj.method();
    
    ClassDemo classObj;
    // classObj.data = 200;  // ERROR: private by default
    classObj.publicMethod();
    
    // Inheritance access levels
    PublicDerived pubDerived;
    pubDerived.showAccess();
    pubDerived.publicMember = 10;  // Still public
    
    ProtectedDerived protDerived;
    protDerived.showAccess();
    // protDerived.publicMember = 20;  // ERROR: now protected
    
    PrivateDerived privDerived;
    privDerived.showAccess();
    privDerived.publicMember = 30;  // Made public again with 'using'
    
    // Encapsulation example
    std::cout << "\n--- Encapsulation Example ---" << std::endl;
    BankAccount account("ACC123", 1000.0);
    
    std::cout << "Account: " << account.getAccountNumber() << std::endl;
    std::cout << "Initial balance: $" << account.getBalance() << std::endl;
    
    account.deposit(250.0);
    std::cout << "After deposit: $" << account.getBalance() << std::endl;
    
    if (account.withdraw(500.0)) {
        std::cout << "After withdrawal: $" << account.getBalance() << std::endl;
    }
    
    // Invalid operations are prevented
    if (!account.withdraw(-100.0)) {
        std::cout << "Invalid withdrawal amount rejected" << std::endl;
    }
    
    if (!account.withdraw(2000.0)) {
        std::cout << "Insufficient funds - withdrawal rejected" << std::endl;
    }
    
    return 0;
}
