import pandas as pd
import os 
import glob 

path = os.getcwd()
tables = glob.glob(os.path.join(path, "*.csv"))

for table in tables:
    df = pd.read_csv(table)

    latex_table = df.to_latex(
        index=False,
        float_format='%.3f',
        caption='TODO', 
        label='tab:TODO',
    )

    print(latex_table, end='\n\n\n')
