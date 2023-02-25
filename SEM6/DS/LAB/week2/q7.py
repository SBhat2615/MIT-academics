import pandas as pd

df1 = pd.DataFrame(
    ['siddhartha', 'preetham', 'bhayya'],
    columns=['Name'],
    index = range(1,4)
)

print(df1)

df2 = pd.DataFrame({
    'Physics' : [94, 96, 92],
    'Chemistry' : [87, 85, 94],
    'Maths' : [88, 93, 97],
    'Biology' : [93, 91, 95]},
    index = range(1,4)
)

print(df2)

df_new = pd.concat([df1, df2], axis=1)

print()
print(df_new)

df_new['Total'] = df_new.iloc[:, 1:5].sum(axis=1)

print()
print(df_new)