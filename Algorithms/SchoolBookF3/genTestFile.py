import random
def gen_input_f3_algo(num_terms, min_range, max_range):
    p1 = []
    for _ in range(num_terms):
        num = random.randint(min_range, max_range)
        p1.append(num)
    return p1

def formatted_print(p1,p2):
    st1 = ",".join([str(elem) for elem in p1])
    st2 = ",".join([str(elem) for elem in p2])
    print(st1,st2,sep=";")

def main():
    num_rows = 2
    num_terms = 10
    min_range = 0
    max_range = 100

    for i in range(0,num_rows):
        p1 = gen_input_f3_algo(num_terms,min_range,max_range)
        p2 = gen_input_f3_algo(num_terms,min_range, max_range)
        formatted_print(p1,p2)

main()