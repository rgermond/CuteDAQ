import csv

def write_dict(filename, d, fields):

    with open(filename,'w') as csvfile:
        writer = csv.DictWriter(csvfile, fieldnames=fields)
        writer.writeheader()

        for i in range(len(d[fields[0]])):
            row = {}
            for key in fields:
                row[key] = d[key][i]
            writer.writerow(row)

def test():
    d = {}
    d['first'] = [1,2,3]
    d['second'] = [1,2,3]
    d['third'] = [1,2,3]

    write_dict('test.csv',d,['first','second','third'])

test()

