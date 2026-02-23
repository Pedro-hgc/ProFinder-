#ifndef USERREPOSITORY_H_
#define USERREPOSITORY_H_

#include "../Cliente.h"
#include "../Fornecedor.h"

class UserRepository {
    private:
    UserRepository();

    public:
    static bool insertClient(const Cliente& _client);
    static bool insertSupplier(const Fornecedor& _supplier);

    static bool getUser(int id);
};

#endif // USERREPOSITORY_H_
