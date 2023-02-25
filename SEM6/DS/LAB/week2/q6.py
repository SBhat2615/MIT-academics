import pandas as pd

student = {
    'Name' : ['siddhartha', 'preetham'],
    'Height' : [160, 165],
    'Qualification' : ['Btech', 'BE']
}

df = pd.DataFrame(student, index=range(1,3))

print(df)

addr = ['Manipal', 'Bangalore']

df.insert(3, 'Address', addr)

print(df)