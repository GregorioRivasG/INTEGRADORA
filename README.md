# APLICACIÓN WEB

  # Se encuentra dentro de la carpeta "AquaSense"
  
  ## Funciones principales de la aplicación
  
  - Monitoreo en tiempo real de parámetros del agua (pH, temperatura, conductividad)
  - Alertas automáticas cuando los valores salen de rangos seguros
  - Generación de reportes en PDF con gráficos históricos
  - Gestión de peceras con CRUD completo
  - Autenticación segura con JWT y roles (admin/empleado)
  - Dashboard interactivo con visualización de datos
  
  ## Tecnologías Utilizadas
  
  ### Backend
  - Node.js (Express)
  - MongoDB (Atlas)
  - Mongoose (ODM)
  - JWT (Autenticación)
  
  ### Frontend
  - React + TypeScript
  - Vite (Build Tool)
  - Chart.js(Gráficos)
  - React Router (Navegación)
  - HTML2PDF (Generación de reportes)
  
  ## Estructura del Proyecto
    aquasense/
      ├── backend/
      │ ├── src/
      │ │ ├── controllers/ # Lógica de negocio
      │ │ ├── models/ # Modelos de MongoDB
      │ │ ├── routes/ # Rutas API
      │ │ └── config/ # Configuraciones
      │ ├── app.js # Servidor principal
      │ └── package.json
      └── frontend/
      ├── src/
      │ ├── components/ # Componentes reutilizables
      │ ├── pages/ # Vistas principales
      │ ├── styles/ # Hojas de estilo
      │ ├── utils/ # Funciones auxiliares
      │ └── App.tsx # Componente raíz
      ├── vite.config.ts # Configuración de Vite
      └── package.json


# APLICACIÓN MÓVIL

  # Se encuentra dentro de la carpeta "APPMOVIL"

  ## Tecnologías Utilizadas
  
  ### Backend
  - Node.js (Runtime)
  - Express.js (Framework web)
  - MongoDB (Base de datos)
  - Mongoose (ODM para MongoDB)
  - JWT (Autenticación)
  - PDFKit (Generación de PDFs en backend)
  
  ### Frontend
  - React Native (Framework móvil)
  - Expo (Desarrollo multiplataforma)
  - React Navigation (Navegación)
  - react-native-chart-kit (Gráficos)
  - expo-print + react-native-view-shot (Generación de PDFs en móvil)
  - Axios (Conexión API)

  ## Estructura del Proyecto
    /APPMOVIL
    ├── backend/
    │   ├── controllers/   # Lógica de endpoints
    │   ├── models/        # Modelos MongoDB
    │   ├── routes/        # Rutas API
    │   └── server.js      # Servidor principal
    └── frontend/
        ├── src/
        │   ├── screens/   # Pantallas de la app
        │   └── navigation # Gestión de rutas
        └── App.js         # Punto de entrada

## Requisitos de instalación
- Node.js v16+
- MongoDB
- Expo CLI (`npm install -g expo-cli`)
- Yarn o npm
- Clonar repositorio
