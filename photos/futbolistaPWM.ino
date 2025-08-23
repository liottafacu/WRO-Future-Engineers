// Definimos los pines del driver H
#define IN1 2
#define IN2 4
#define IN3 7
#define IN4 8

// Pines de PWM para controlar la velocidad
#define PWM_A 6
#define PWM_B 9

int velocidad = 255; // Velocidad inicial al máximo

void setup() {
    // Configuración de los pines como salida
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(PWM_A, OUTPUT);
    pinMode(PWM_B, OUTPUT);

    // Inicializamos la comunicación serie para Bluetooth
    Serial.begin(9600);
}

void loop() {
    if (Serial.available()) {
        char command = Serial.read(); // Leer el comando Bluetooth

        // Si el comando es un número del '1' al '9', ajusta la velocidad
        if (command >= '1' && command <= '9') {
            int newSpeed = map(command - '0', 1, 9, 28, 255); // Convertir char a int y mapear
            velocidad = newSpeed;
        }

        // Aplicar la velocidad en los pines PWM
        analogWrite(PWM_A, velocidad);
        analogWrite(PWM_B, velocidad);

        // Control de movimiento
        switch (command) {
            case 'F': // Avanzar
                digitalWrite(IN1, LOW);
                digitalWrite(IN2, HIGH);
                digitalWrite(IN3, LOW);
                digitalWrite(IN4, HIGH);
                break;
            
            case 'B': // Retroceder
                digitalWrite(IN1, HIGH);
                digitalWrite(IN2, LOW);
                digitalWrite(IN3, HIGH);
                digitalWrite(IN4, LOW);
                break;
            
            case 'L': // Girar a la izquierda
                digitalWrite(IN1, LOW);
                digitalWrite(IN2, HIGH);
                digitalWrite(IN3, HIGH);
                digitalWrite(IN4, LOW);
                break;
            
            case 'R': // Girar a la derecha
                digitalWrite(IN1, HIGH);
                digitalWrite(IN2, LOW);
                digitalWrite(IN3, LOW);
                digitalWrite(IN4, HIGH);
                break;
            
            case 'S': // Detenerse
                digitalWrite(IN1, LOW);
                digitalWrite(IN2, LOW);
                digitalWrite(IN3, LOW);
                digitalWrite(IN4, LOW);
                break;
        }
    }
}
