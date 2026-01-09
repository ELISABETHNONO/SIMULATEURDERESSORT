""" 
Système de build incrémental pour le simulateur de ressorts 
"""


import os 
import subprocess 
import hashlib 
from pathlib import Path 
import sys 
class BuildSystem: 
    def __init__(self): 
        self.ProjectDir = Path(__file__).parent 
        self.SrcDir = self.ProjectDir / "src" 
        self.BuildDir = self.ProjectDir / "build" 
        self.ObjDir = self.BuildDir / "obj" 
        self.DepsDir = self.BuildDir / "deps" 

        # Configuration MSYS2 ucrt64 
        self.Compiler = "clang++" 
        self.CxxFlags = "-std=c++17 -O2 -Wall -Wextra -Wno-missing-field initializers" 
        
        self.Libs = "-Llib/SDL3/lib -lSDL3 -limm32 -ldwmapi" 
        
        self.Output = self.BuildDir / "spring_simulator.exe" 
    def EnsureDirs(self): 
        """Crée les répertoires nécessaires""" 
        for dir in [self.BuildDir, self.ObjDir, self.DepsDir]: 
             dir.mkdir(exist_ok=True) 
    def GetSourceFiles(self):
        """Récupère tous les fichiers .cpp""" 
        cppFiles = [] 
        for root, _, files in os.walk(self.SrcDir): 
            for file in files: 
                if file.endswith(".cpp"): 
                    cppFiles.append(Path(root) / file) 
        return cppFiles 
   
    def ComputeHash(self, filepath): 
        """Calcule le hash MD5 d'un fichier""" 
        with open(filepath, 'rb') as f: 
            return hashlib.md5(f.read()).hexdigest() 

    def NeedsRecompile(self, cppFile, objFile): 
        """Vérifie si un fichier doit être recompilé""" 
        if not objFile.exists(): 
            return True 
        
        # Vérifie si le .cpp a changé 
        currentHash = self.ComputeHash(cppFile) 
        hashFile = self.DepsDir / f"{cppFile.stem}.hash" 
        if hashFile.exists(): 
            with open(hashFile, 'r') as f: 
                cachedHash = f.read().strip() 
            if currentHash == cachedHash: 
                return False 

        # Sauvegarde le nouveau hash 
        with open(hashFile, 'w') as f: 
            f.write(currentHash) 
        
        return True 
    
    def CompileFile(self, cppFile): 
        """Compile un fichier .cpp en .o""" 
        objFile = self.ObjDir / f"{cppFile.stem}.o" 
        
        if not self.NeedsRecompile(cppFile, objFile): 
            print(f"  [CACHE] {cppFile.name}") 
            return objFile 
        
        print(f"  [CC] {cppFile.name}") 
        # Inclusions 
        includes = [ 
            "-Ilib/SDL3/include", 
            "-Ilib/ImGui", 
            "-Ilib/ImGui/backends", 
            f"-I{self.SrcDir}" 
        ] 

        # Commande de compilation 
        cmd = [self.Compiler] + self.CxxFlags.split() + includes + [ 
            "-c", str(cppFile), 
            "-o", str(objFile) 
        ] 

        try: 
            subprocess.run(cmd, check=True)
            return objFile 
        except subprocess.CalledProcessError as e: 
            print(f"Erreur de compilation {cppFile.name}: {e}") 
            sys.exit(1) 
    def BuildImGui(self): 
        """Compile les fichiers ImGui""" 
        print("\n[BUILD] ImGui") 
        
        imguiDir = self.ProjectDir / "lib" / "ImGui" 
        backendsDir = imguiDir / "backends" 
        
        imguiFiles = [ 
            imguiDir / "imgui.cpp", 
            imguiDir / "imgui_draw.cpp", 
            imguiDir / "imgui_tables.cpp", 
            imguiDir / "imgui_widgets.cpp", 
            backendsDir / "imgui_impl_sdl3.cpp", 
            backendsDir / "imgui_impl_sdlrenderer3.cpp" 
        ] 
        
        objFiles = [] 
        for file in imguiFiles: 
            if not file.exists(): 
                print(f"Erreur: Fichier ImGui manquant: {file}") 
                sys.exit(1) 
            
            objFile = self.ObjDir / f"imgui_{file.stem}.o" 
            
            # Toujours recompiler ImGui pour simplifier 
            print(f"  [CC] {file.name}") 
            includes = [ 
                "-Ilib/SDL3/include", 
                f"-I{imguiDir}", 
                f"-I{backendsDir}" 
            ] 
           
            cmd = [self.Compiler] + self.CxxFlags.split() + includes + [ 
                "-c", str(file), 
                "-o", str(objFile) 
            ] 
            
            subprocess.run(cmd, check=True) 
            objFiles.append(objFile) 
        return objFiles 

    def Link(self, objFiles): 
        """Link les fichiers objets en exécutable""" 
        print(f"\n[LINK] {self.Output.name}") 
        objPaths = [str(f) for f in objFiles] 
        cmd = [self.Compiler] + objPaths + self.Libs.split() + [ 
            "-o", str(self.Output) 
        ] 
        try: 
            subprocess.run(cmd, check=True) 
            print(f"✓ Build réussi: {self.Output}") 
        except subprocess.CalledProcessError as e: 
            print(f"Erreur de link: {e}") 
            sys.exit(1) 
    
    def CopyDLLs(self): 
        """Copie les DLLs nécessaires""" 
        sdlDll = self.ProjectDir / "lib" / "SDL3" / "bin" / "SDL3.dll" 
        if sdlDll.exists(): 
            import shutil 
            shutil.copy2(sdlDll, self.BuildDir / "SDL3.dll") 
            print("✓ DLL SDL3 copiée") 
    def Build(self): 
        """Build complet du projet""" 
        print("=== Build du simulateur de ressorts ===") 
        self.EnsureDirs() 
        
        # Compilation ImGui 
        imguiObjs = self.BuildImGui() 
        
        # Compilation des fichiers source du projet 
        sourceFiles = self.GetSourceFiles() 
        objFiles = imguiObjs 
       
        print("\n[BUILD] Projet principal") 
        for cppFile in sourceFiles: 
            objFile = self.CompileFile(cppFile) 
            objFiles.append(objFile) 
        
        # Link 
        if objFiles: 
            self.Link(objFiles) 
# Copie des DLLs 
        self.CopyDLLs() 
        
        print("\n✓ Prêt! Exécutez avec: python run.py") 

if __name__ == "__main__": 
    builder = BuildSystem() 
    builder.Build() 