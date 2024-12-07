import glob
import subprocess

for filename in glob.glob("./cases/*.in"):
    fin = open(filename, 'r')
    fout = open(filename.replace('.in', '.out'), 'r')
    inp = fin.read()
    out = fout.read()

    p = subprocess.run(['./bin/main'], input=inp, capture_output=True, text=True)
    if p.stdout == out or p.stdout+'\n' == out:
        print(filename, 'OK')
    else:
        print(filename, 'FALHOU !!!')

    fin.close()
    fout.close()