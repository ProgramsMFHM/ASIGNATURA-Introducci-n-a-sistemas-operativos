import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import os

# Formato para eliminar ceros finales en LaTex
def custom_format(x):
    # Not Cientifica
    formatted_str = ('%.6g' % x)

    if '.' in formatted_str:
        # Erase Final Ceros after the decimal point
        formatted_str = formatted_str.rstrip('0').rstrip('.')

    return formatted_str

def CreateLatexTable(csvFilePath, latexFilePath, programNum):
    data = pd.read_csv(csvFilePath)

    ### Texto para agregar en latex
    latex_line_1 = "\center\n" # Centering Table
    latex_line_2 = "\hline \multicolumn{4}{|c|}{Datos obtenidos de programa} \\\\\n\n" # Pie de tabla

    ### Generando contenido de tabla
    latex_table = (
        data[['Item',"Value", "Partial", "Total"]]
        .rename(columns={
            "Item": "Intem",
            "Value": "Valor",
            "Partial": "Tiempo Partial",
            "Total": "Tiempo acumulado"
        })
        .to_latex(
            index=False,
            float_format=custom_format,
            caption="Datos correspondientes al archivo programa"+str(programNum)+".csv luego de 25 segundos",
            label="tab:programa"+str(programNum),
            escape=False,
            column_format="|c|c|c|c|"
        )
    )

    ### Editando contenido de tabla para mejor visibilidad
    latex_lines = latex_table.split('\n')
    latex_lines.insert(1, latex_line_1)
    latex_lines[0] = "\\begin{table}[ht!]"
    latex_lines.insert(-4, latex_line_2)
    latex_table = '\n'.join(latex_lines)

    ### Creando archivo latex
    with open(latexFilePath, "w") as Tfile:
        Tfile.write(latex_table)


# Data de archivos CSV
## Archivo1
fileName = 'infoproceso1'
path_experient = os.path.join("../../", "build", fileName+".csv")
path_latex = os.path.join("../", "Latex/src/tables/"+str(fileName)+".tex") # Archivo
CreateLatexTable(path_experient, path_latex, 1)

## Archivo2
fileName = 'infoproceso2'
path_experient = os.path.join("../../", "build", fileName+".csv")
path_latex = os.path.join("../", "Latex/src/tables/"+str(fileName)+".tex") # Archivo
CreateLatexTable(path_experient, path_latex, 2)

## Archivo3
fileName = 'infoproceso3'
path_experient = os.path.join("../../", "build", fileName+".csv")
path_latex = os.path.join("../", "Latex/src/tables/"+str(fileName)+".tex") # Archivo
CreateLatexTable(path_experient, path_latex, 3)