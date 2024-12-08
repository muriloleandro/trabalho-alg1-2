import glob
import subprocess

failed = []
worked = []

for filename in glob.glob("./cases/*.in"):
    fin = open(filename, 'r')
    fout = open(filename.replace('.in', '.out'), 'r')
    inp = fin.read()
    out = fout.read()

    p = subprocess.run(['./bin/main'], input=inp, capture_output=True, text=True)
    if p.stdout == out or p.stdout+'\n' == out:
        worked.append(filename)
    else:
        failed.append(filename)

    fin.close()
    fout.close()

print(f'Passed: {len(worked)}')
print(f'Failed: {len(failed)}')
for fail in failed:
    print(fail)