plugins {
    kotlin("jvm") version "2.0.0"
    id("maven-publish")
}

group = "cum.jesus.jesusasm"
version = "1.0"

repositories {
    mavenCentral()
}

dependencies {
    implementation("org.jetbrains.kotlin:kotlin-reflect:2.0.0")
}

publishing {
    publications {
        create<MavenPublication>("maven") {
            from(components["java"])
        }
    }
}

kotlin {
    jvmToolchain(8)
}