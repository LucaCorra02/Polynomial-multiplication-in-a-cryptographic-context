import random
import sys
import re

def open_file(file_name):
    tempi = []
    with open(file_name, 'r') as file:
        for line in file:
            if "->" in line:
                total_time_part = line.split("->")[-1].strip()
                if ":" in total_time_part:
                    time_str = total_time_part.split(":")[-1].strip()
                    total_time = float(time_str)
                    tempi.append(total_time)
    return tempi


def calc_avg(tempi):
    if len(tempi) == 0:
        return 0.0
    return sum(tempi) / len(tempi)

def main():
    args = sys.argv[1:]
    tempi = open_file(args[0])
    avg = calc_avg(tempi)
    print("Media: ",avg*1000,"ms")

    #Su 150 volte
    #SumInt1 Media:  4.395073333333335 ms
    #SumInt2 Media:  4.260146666666666 ms
    #SumInt4 Media:  4.571006666666668 ms
    #SumInt6 Media:  4.644833333333332 ms
    #SUmInt7 Media:  5.06732 ms

    #ProdInt1 Media:  4.795200000000002 ms
    #ProdInt2 Media:  4.679073333333336 ms
    #ProdInt4 Media:  4.885559999999998 ms
    #ProdInt6 Media:  4.642533333333336 ms

    #Su 500 volte
    #SumIntV1 Media:  3.4496459999999978 ms
    #SumIntV2 Media:  3.508280000000002 ms
    #SumIntv4 Media:  3.9148500000000017 ms
    #SumIntV6 Media:  4.709931999999998 ms
    #SumIntv7 Media:  3.501869999999999 ms

    #INT V1

    #Su 200 volte:
    #SumIntV1 1 cifre Media:  455.6342050000003 ms
    #SumIntV1 2 cifre Media:  483.07314000000014 ms
    #sumIntv1 3 cifre Media:  459.2422299999999 ms
    #SumIntV1 4 cifre Media:  470.69358800000015 ms
    #SumIntv1 5 cifre Media:  491.30121 ms
    #SumIntv1 6 cifre Media:  470.1444199999997 ms

    #ProdIntV1 1 cifra Media:  420.5687850000003 ms
    #ProdIntV1 2 cifre Media:  455.36526500000014 ms
    #ProdIntV1 3 cifre Media:  459.3101700000002 ms
    #ProdIntV1 4 cifre Media:  463.40212999999994 ms
    #ProdIntV1 5 cifre Media:  466.2621400000003 ms
    #ProdIntV1 6 cifre Media:  472.607935 ms

    #INT

    #IntSum 1 cifra Media:  446.9476250000002 ms
    #IntSum 2 cifre Media: 446.6315900000002 ms
    #IntSum 3 cifre Media: 439.7583500000002 ms
    #IntSum 4 cifre Media: 434.0608449999996 ms
    #IntSum 5 cifre Media: 448.4485600000002 ms
    #IntSum 6 cifre Media: 449.53535999999986 ms


    #IntProd 1 cifra Media:  385.80845499999987 ms
    #IntProd 2 cifra Media:  408.9091950000002 ms
    #IntProd 3 cifra Media:  395.5779900000003 ms
    #IntProd 4 cifre Media:  435.040085 ms
    #IntProd 5 cifre Media:  420.83389500000027 ms
    #IntProd 6 cifre Media:  432.0796249999999 ms

    #BOOL

    #BoolSum 1 cifra Media:  687.84888 ms
    #BoolSum 2 cifra Media:  663.6270199999999 ms
    #BoolSum 3 cifra Media:  669.5332649999998 ms
    #BoolSum 4 cifra Media:  664.76535 ms
    #BoolSum 5 cifra Media:  692.640335 ms
    #BoolSum 6 cifre Media:  809.2354550000005 ms

    #BoolProd 1 cifra Media:  711.4271099999995 ms
    #BoolProd 2 cifra Media:  721.087705 ms
    #BoolProd 3 cifra Media:  718.0519699999998 ms
    #BoolProd 4 cifra Media:  732.28889 ms
    #Media:  727.9220300000009 ms
    #Media:  750.89389 ms



















    #ProdIntV1 1 Media : 4.8234 ms
    #ProdIntV2 2 Media:  5.119946666666666 ms










    #SumBool1 = 11.002283999999996 ms
    #ProdBool1 = 8.900487999999996 ms
    #SumInt1 = 3.904572000000001 ms
    #ProdInt1 = 3.239713999999997 ms


    #SumBool2 Media:  12.462761999999987 ms
    #ProdBool2 Media:  12.002687999999992 ms
    #SumInt2 = Media:  4.530682000000002 ms
    #ProdInt2 = Media:  4.0223739999999975 ms


    #SumBool3 = Media:  12.551346000000013 ms
    #ProdBool3 = Media:  12.116530000000013 ms
    #SumInt3 = Media:  4.2429960000000015 ms
    #ProdInt3 = Media:  4.090098000000002 ms


    #su 100 ripetizioni
    #F9PROD_POSITIVO = Media: 139.19287000000003 ms  V2 = Media:  132.60771999999997 ms v3 = Media:  34.585840000000005 ms
    #F9PROD_IMG_NEG = Media:  226.22134000000005 ms V3 = Media:  140.11504 ms v3 = Media:  37.53094000000001 ms
    #F9PROD_NEG Media:  196.22944000000004 ms Media:  179.50024 ms v3 = Media:  50.34518000000001 ms


main()