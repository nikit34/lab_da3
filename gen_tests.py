import numpy as np
import string
from tqdm import tqdm


with open('test1.txt', 'w') as f:
    for _ in tqdm(range(1000)):
        s = str(np.random.choice(['+', '=', '-', '!'], 1, p=[0.7, 0.15, 0.1, 0.05])[0])
        if s == '=' or s == '!':
            f.write(f'{s}\n')
            continue
        k = ''.join(np.random.choice(np.array(list(string.ascii_lowercase + string.digits)), 5))
        if s == '-':
            f.write(f'{s} {k}\n')
            continue
        v = str(np.random.randint(100))
        f.write(f'{s} {k} {v}\n')