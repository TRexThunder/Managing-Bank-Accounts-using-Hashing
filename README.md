# Managing-Bank-Accounts-using-Hashing
Course Project (COL106) under Prof. Subodh Sharma [August 2023]: Maintained a reliable hashmap to manage a vast array of bank accounts by implementing well-optimized hash functions and collision resolution methods such as chaining, linear probing, quadratic probing and cubic probing.
## Description of Functions
1. void createAccount(string id, int count): Creates a new account with the given id and initial count value.
1. vector<int> getTopK(int k): Retrieves the top k balances values from the database.
1. int getBalance(string id): Returns the current balance of the account identified by the provided id.
1. void addTransaction(string id, int count): Adds a transaction of count value (can be positive or negative) to the account specified by the id.
1. bool doesExist(string id): Checks if an account with the given id exists in the database.
1. int databaseSize(): Returns the total number of accounts currently stored in the database.
1. int hash(string id): Computes the hash value for the given id.
1. bool delete(string id): Deletes the key stored in the database.
