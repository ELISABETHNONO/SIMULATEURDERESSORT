"""Nettoyage des fichiers de build""" 


import shutil 
from pathlib import Path 

def Main(): 
    buildDir = Path("build") 
    if buildDir.exists(): 
        print("Nettoyage des fichiers de build...") 
        shutil.rmtree(buildDir) 
        print("✓ Répertoire 'build' supprimé") 
    else: 
        print("Aucun build à nettoyer.") 

if __name__ == "__main__": 
    Main()
    