#include "filemanager.h"
FileManager::FileManager(const QString &fileName)
{
    this->file =new QFile(fileName);
}
void FileManager::saveKami(const QVector<Layer> &layers, QColor background) {
    file->open(QIODevice::WriteOnly);
    QDataStream out(file);
    out << KAMI_HEADER;
    out.setVersion(QDataStream::Qt_4_0);
    out << background;
    out << layers.length();
    for (int i = 0; i < layers.length(); i++) {
        const Layer &layer = layers.at(i);
        out << static_cast<qint16>(layer.blendingMode);
        out << layer.visible;
        out << layer.data.length();
        for (int j = 0; j < layer.data.length(); j++) {
            const Stroke &stroke = layer.data.at(j);
            out << stroke.fillColor;
            out << stroke.outlineColor;
            out << static_cast<qint16>(stroke.type);
            out << static_cast<qint16>(stroke.mode);
            out << stroke.sStart;
            out << stroke.sEnd;
            out << stroke.pen;
            out << stroke.brush;
            out << stroke.data.length();
            for (int k = 0; k < stroke.data.length(); k++) {
                out << stroke.data.at(k);
            }
        }
    }
    file->close();
}
QVector<Layer> FileManager::loadKami() {
    file->open(QIODevice::ReadOnly);
    QDataStream in(file);
    quint16 header;
    QVector<Layer> layers;
    in >> header;
    if (header != KAMI_HEADER) {
        std::cout << "Not a Kami file. with header " << std::hex<< header << std::endl;
    } else {
        in.setVersion(QDataStream::Qt_4_0);
        int l1;
        in >> background;
        in >> l1;
        for (int i = 0; i < l1; i++) {
            Layer layer;
            qint16 blend;
            int l2;
            in >> blend;
            layer.blendingMode = BlendingMode(blend);
            in >>layer.visible;
            in >> l2;
            for (int j = 0; j < l2; j++) {
                Stroke stroke;
                qint16 t, m;
                int l3;
                in >> stroke.fillColor;
                in >> stroke.outlineColor;
                in >> t; stroke.type = StrokeType(t);
                in >> m; stroke.mode = StrokeMode(m);
                in >> stroke.sStart;
                in >> stroke.sEnd;
                in >> l3;
                for (int k = 0; k < l3; k ++) {
                    QRectF rect;
                    in >> rect;
                    stroke.data.append(rect);
                }
                layer.data.append(stroke);
            }
            layers.append(layer);
        }
    }
    file->close();
    return layers;
}
