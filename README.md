<div align="center">

# 🚗 Mindful Drive Pro

### A camera-based driver-awareness prototype for Arduino UNO Q

Live camera streaming · Edge Impulse object detection · Arduino hardware

[![Platform](https://img.shields.io/badge/Platform-Arduino%20UNO%20Q-00979D?style=for-the-badge&logo=arduino&logoColor=white)](https://docs.arduino.cc/hardware/uno-q/)
[![AI](https://img.shields.io/badge/AI-Edge%20Impulse-5B4BDB?style=for-the-badge)](https://edgeimpulse.com/)
[![Language](https://img.shields.io/badge/Python%20%2B%20JavaScript-Stack-3776AB?style=for-the-badge&logo=python&logoColor=white)](#-technology-stack)

</div>

> **Mindful Drive Pro** explores how a compact edge-computing board can combine a camera stream, computer vision, and a simple hardware response. The repository currently demonstrates live **general object detection**; it does not yet contain a trained or validated driver-drowsiness classifier.

---

## ✨ What it does

- Pairs a phone camera with the Arduino UNO Q using the Arduino IoT Remote app and a QR code.
- Streams portrait video to the board over the local network.
- Runs an Edge Impulse object-detection model and displays labels and confidence scores in a browser UI.
- Lets the user adjust the detection confidence threshold while the stream is active.
- Shows the five most recent detections and visual feedback for selected everyday objects.
- Connects Python detection events to the UNO Q built-in LED through Arduino Router Bridge. The Python callback currently checks for a `close` label; confirm that this matches the labels in the deployed model.

## 🧭 How it works

```text
Phone camera
    │  Arduino IoT Remote / encrypted WebSocket
    ▼
Arduino UNO Q ── VideoObjectDetection (Edge Impulse .eim model)
    │                         │
    │                         ├── labels + confidence ──► Browser dashboard
    │                         └── bridge call ──────────► Built-in LED
    └── WebUI + QR pairing + confidence-threshold control
```

The Python application creates a short pairing secret, starts the WebSocket camera and detection brick, and sends status and detection events to the web interface. The browser renders the stream, QR code, adjustable confidence threshold, feedback, and recent detections.

## 🧠 Computer-vision model and training

The app is configured to use an **Edge Impulse object-detection model**:

| Setting | Repository configuration |
| --- | --- |
| Model identifier | `ei-model-1034592-3` |
| Model file | `/home/arduino/.arduino-bricks/ei-models/mindful-drive-pro-.eim` |
| Detection brick | `arduino:video_object_detection` |
| Initial confidence threshold | `0.5` (can be changed in the UI) |

The model file is fetched/managed by the Arduino video object-detection brick; it is not checked into this repository. The repository does **not** document the training dataset, class list, model architecture, training settings, or evaluation results, so those details cannot be confirmed here. The app’s feedback UI includes labels such as cat, cell phone, clock, cup, dog, and potted plant; this alone does not establish the model’s full label set.

### Training or updating the model

To produce a new model for this project, use an Edge Impulse object-detection workflow:

1. Collect representative camera images for the intended use case and annotate each target object with bounding boxes and consistent labels.
2. Split the annotated data into training, validation, and test sets. Include realistic variation in lighting, distance, camera angle, and background.
3. Train an object-detection model in Edge Impulse, then evaluate it on held-out data. Record the dataset source, class list, training settings, and metrics alongside the model.
4. Export/deploy a model compatible with the Arduino video object-detection brick and configure its model file and identifier in `app.yaml`.
5. Test the exported model on the UNO Q and tune the confidence threshold against real camera streams.

For actual drowsiness detection, the dataset and labels must represent relevant driver states, and the model must be evaluated for that purpose. This project is a prototype, not a safety-certified driver-monitoring system.

## 🧰 Technology stack

| Area | Technologies |
| --- | --- |
| Edge hardware | Arduino UNO Q |
| Runtime and app backend | Python, Arduino App Lab / `arduino.app_utils` |
| Camera and inference | `WebSocketCamera`, `VideoObjectDetection`, Edge Impulse `.eim` model |
| Web interface | HTML, CSS, JavaScript, Arduino `WebUI` |
| Browser utilities | Socket.IO, QRCode.js |
| Hardware control | Arduino sketch, `Arduino_RouterBridge.h`, built-in LED |

## 🚀 Getting started

### Requirements

- Arduino UNO Q set up with Arduino App Lab
- Arduino IoT Remote app on an iOS or Android phone
- Phone and board connected to the same network
- A computer or phone browser to open the app UI

### Run the project

1. Open this project in Arduino App Lab on the UNO Q and run the app.
2. Open the app UI using the URL provided by Arduino App Lab if it does not open automatically.
3. Open Arduino IoT Remote on your phone, choose **Stream phone camera to UNO Q**, and scan the QR code shown in the UI.
4. Start the camera stream. Detections, confidence scores, and the latest results will appear in the dashboard.
5. Adjust the confidence threshold in the UI to change which detections are reported.

## 📁 Project layout

```text
.
├── app.yaml             # Arduino App Lab configuration and model settings
├── python/main.py       # Camera, inference, UI events, and LED bridge calls
├── sketch/sketch.ino    # UNO Q built-in LED bridge handler
└── assets/              # Web UI, styles, fonts, and images
```

## 👨‍💻 About the developer

Created by **Gavindu Achintha** as an Arduino UNO Q and edge-computer-vision project.

[![GitHub](https://img.shields.io/badge/GitHub-Gavinduachintha-181717?style=for-the-badge&logo=github)](https://github.com/Gavinduachintha)

## ⚠️ Safety note

This is an experimental learning project. It is not a certified driver-monitoring, medical, or vehicle-safety system. Do not rely on it to determine whether someone is safe to drive.

---

<div align="center">

Built with curiosity, computer vision, and Arduino.

</div>
