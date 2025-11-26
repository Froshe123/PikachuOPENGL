# ⭐ **Projet Pikachu – Synthèse d’Image (OpenGL)**

Ce projet a été réalisé dans le cadre de ma **3ᵉ année de Licence Informatique (L3)** à l’**Université de Bourgogne**, pour la matière *Synthèse d’Image*.  
L’objectif est de **modéliser et animer un Pikachu 3D** en utilisant **OpenGL**, des primitives géométriques simples et une gestion manuelle des textures.

---

## 🔍 **Objectifs du projet**

- Manipuler **OpenGL** en C++
- Construire un modèle 3D à partir de primitives (sphères, cylindres, cônes…)
- Gérer :
  - transformations (translation, rotation, scale)
  - lumières directionnelles et ponctuelles
  - textures personnalisées
- Ajouter plusieurs types **d’animations 3D**

---

## 🎞️ **Animations du Pikachu**

Le Pikachu possède **deux types d’animations**, comme décrit dans le rapport (pages 9 à 12) :contentReference[oaicite:1]{index=1} :

### 🔁 Animation passive (permanente)
Une animation continue est jouée en boucle sans interaction de l’utilisateur.  
Elle simule la **respiration** et de légers mouvements du personnage :

- balancement des bras  
- balancement des oreilles  
- rotation de la queue  
- variations d’angles pour donner un mouvement naturel  

Cette animation tourne automatiquement via la fonction `IdleAnimation()`.

---

### ⚡ Animation active (déclenchée par la barre d’espace)
Lorsque l'utilisateur appuie sur la touche **Espace**, une animation spéciale se déclenche :

- le **chapeau** de Pikachu s’ouvre  
- une **balle** (objet animé) sort du chapeau  
- la balle suit un mouvement vertical  
- une fois retombée, le chapeau se referme  

Le rapport illustre cette animation avec un schéma (page 11) et détaille le fonctionnement du flag `is_started` déclenché par la touche espace :contentReference[oaicite:2]{index=2}.

---

## ☀️ **Lumières et éclairage**

Le projet utilise **deux types de sources lumineuses OpenGL**, comme décrit pages 12 à 14 du rapport :contentReference[oaicite:3]{index=3} :

### 💡 Lumière directionnelle (GL_LIGHT0)
- éclaire la scène comme une **lumière solaire**  
- provient du haut et de la droite  
- utilise des composants ambiants, diffus et spéculaires  
- permet d’obtenir un rendu propre et homogène du modèle

### 🔵 Lumière ponctuelle attachée au chapeau (GL_LIGHT1)
- lumière locale attachée à la position du chapeau  
- se déplace avec l’animation de la balle  
- possède une couleur légèrement bleutée  
- génère un effet lumineux dynamique pendant l’animation

---

## 🎨 **Textures**

Deux textures principales sont utilisées :

- **carte.jpg** : sol sur lequel Pikachu est posé  
- **pokeball.jpg** : appliquée sur une primitive paramétrique (le cylindre)  

Les coordonnées de texture sont entièrement calculées **manuellement** (comme expliqué pages 7–9) :contentReference[oaicite:4]{index=4}.

---

## 🧱 **Contenu du projet**

- Fichiers C++ construisant les primitives et le modèle  
- Modèle de Pikachu (tête, bras, oreilles, queue, chapeau…)  
- Gestion des textures et lumières  
- Animations passive et active  
- Fichier `main.cpp` contenant la boucle OpenGL et la configuration de la scène  

---

## 🛠️ **Technologies utilisées**

- **C++**
- **OpenGL**
- **GLUT / FreeGLUT**

---

## ▶️ **Compilation et exécution**

Le projet nécessite une configuration OpenGL fonctionnelle (GL, GLU, GLUT).  
Une fois compilé, l’exécution affiche le personnage texturé, éclairé et animé.

---

## 🎯 **Résultat**

Le programme produit un **Pikachu 3D animé**, complet, modélisé à partir de primitives géométriques, texturé, éclairé par deux sources lumineuses, avec :

- une **animation passive** continue  
- une **animation active** déclenchée par l’utilisateur

---

## 👤 **Auteur**

Projet réalisé par **Axel Kramer et Arsene Cléry** (L3 Informatique – Université de Bourgogne).

