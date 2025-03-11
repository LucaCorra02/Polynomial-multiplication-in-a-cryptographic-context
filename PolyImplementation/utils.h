unsigned int** create_vector(unsigned int num_operations, unsigned int num_operands);

void free_vector(unsigned int **operations, unsigned int num_operations);

int load_vector(char *filename, unsigned int num_operations, unsigned int **operations);

int read_file(char *filename, unsigned int num_operations, unsigned int** operations);


