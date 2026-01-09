"""Script d'exécution""" 

import subprocess 
import sys 
from pathlib import Path 

def Main(): 
    exePath = Path("build/spring_simulator.exe") 
    
    if not exePath.exists()   
        print("Erreur: Exécutable non trouvé. Lancez d'abord:") 
        print("  python build.py") 
        sys.exit(1) 
    
    print("Lancement du simulateur de ressorts...") 
    print("(Appuyez sur Ctrl+C pour quitter)\n") 
      
    try: 
        # Exécute depuis le répertoire build pour trouver la DLL 
        subprocess.run([str(exePath)], cwd=exePath.parent) 
    except KeyboardInterrupt: 
        print("\n\nSimulateur arrêté par l'utilisateur.") 
    except FileNotFoundError: 
        print("Erreur: Exécutable non trouvé.") 
    except Exception as e: 
        print(f"Erreur d'exécution: {e}") 
 
if __name__ == "__main__": 
    Main() 