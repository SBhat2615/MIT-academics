import pandas as pd

df = pd.DataFrame({
    'Name' : ['Annie', 'Diya', 'Charles', 'James'],
    'Quiz1' : [8, 9, 7.5, 8],
    'Insem1' : [11, 14, 14.5, 13],
    'Quiz2' : [9.5, 6.5, 8.5, 9],
    'Insem2' : [12.5, 13.5, 14.5, 15]},
    index = range(1,5)
)

df['Total'] = df.iloc[:, 1:5].sum(axis=1)

df.loc['Mean'] = df.mean(axis=0, numeric_only=True)

print(df)