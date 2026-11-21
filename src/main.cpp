#include <sil/sil.hpp>
#include <iostream>
#include "random.hpp"
#include <cmath>
#include <string>
#include <complex>


// Fonction 1 : garder uniquement le vert
void keep_green_only(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        color.r = 0.f;
        color.b = 0.f;
    }
}




// Fonction 2 : échanger le rouge et le bleu
void channels_swap(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        std::swap(color.r, color.b);
    }
}





// Fonction 3 : Noir et blanc
void noirblanc(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        float moyenne = (color.r + color.g + color.b) / 3.f;

        color.r = moyenne;
        color.g = moyenne;
        color.b = moyenne;
    }
}





// Fonction 4 : Negatif
void negatif(sil::Image &image)
{
    for (glm::vec3 &color : image.pixels())
    {
        color.r = 1.f - color.r;
        color.g = 1.f - color.g;
        color.b = 1.f - color.b;
    }
}





// Fonction 5 : degrade
void degrade(sil::Image& image)
{

    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            // progression
            float valeur = static_cast<float>(x) / (image.width() - 1);

            image.pixel(x, y).r = valeur;
            image.pixel(x, y).g = valeur;
            image.pixel(x, y).b = valeur;
        }
    }

}




// Fonction 6 : miroir
void miroir(sil::Image &image)
{
    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            
            int miroir = image.width() - 1 - x;
            
            if (x < miroir)
                {
                glm::vec3 couleur = image.pixel(x, y);
                glm::vec3 couleur_miroir = image.pixel(miroir, y);

                image.pixel(x, y) = couleur_miroir;
                image.pixel(miroir, y) = couleur; 
                }
            
            //std::cout << "x : " << x << " / miroir : " << miroir << std::endl;

        }
    }

}





// Fonction 7 : image bruitée
void bruitee(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            
            if (true_with_probability(0.1f))
            {
                // modifier le pixel
                image.pixel(x, y).r = random_float(0.f, 1.f);
                image.pixel(x, y).g = random_float(0.f, 1.f);
                image.pixel(x, y).b = random_float(0.f, 1.f);
            }

        }
    }

}





// Fonction 8 : rota 90°
void rota90(sil::Image &image)
{
    

    int new_width = image.height();
    int new_height = image.width();

    sil::Image new_image{new_width, new_height};

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            
            new_image.pixel(image.height() - 1 - y, x) = image.pixel(x, y);

        }
    }
    image = new_image;

}





/////// A REVOIR ????
// Fonction 9 : rgb split
void rgbsplit(sil::Image &image)
{
    int d = 20; // distances entre les repetitions
    sil::Image new_image{image.width(), image.height()};

    for (int x=0; x < image.width(); x++)
    {
        for (int y=0; y < image.height(); y++)
        {
            if (x>=d && x + d < image.width())
            {
            new_image.pixel(x, y).r = image.pixel(x+d, y).r;
            new_image.pixel(x, y).g = image.pixel(x, y).g;
            new_image.pixel(x, y).b = image.pixel(x-d, y).b;
            
            }

        else (new_image.pixel(x, y) = image.pixel(x, y));

        }
    }
    image = new_image;

}





// Fonction 10 : luminosite
void luminosite(sil::Image &image)
{
    
    sil::Image new_image{image.width(), image.height()};

    for (int x = 0; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y).r = pow(image.pixel(x, y).r, 2.f); // --> 0.5f pour eclaircir
            image.pixel(x, y).g = pow(image.pixel(x, y).g, 2.f); // --> 0.5f pour eclaircir
            image.pixel(x, y).b = pow(image.pixel(x, y).b, 2.f); // --> 0.5f pour eclaircir
        }
    }
}






// Fonction 11 : disque

void disque(sil::Image &image, int centre_x, int centre_y)
{
    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            // Si le pixel est dans le disque -> blanc
            if (pow(x - centre_x, 2) + pow(y - centre_y, 2) <= pow(100, 2))
            {
                image.pixel(x, y).r = 1.f;
                image.pixel(x, y).g = 1.f;
                image.pixel(x, y).b = 1.f;
            }
        }
    }
}








// Fonction 12 : cercle
void cercle(sil::Image &image, int centre_x, int centre_y)
{
    int rayon = 100;
    int epaisseur = 10;

    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            int dcarre = pow(x - centre_x, 2) + pow(y - centre_y, 2);

            if (pow(rayon - epaisseur, 2) <= dcarre && dcarre <= pow(rayon, 2))
            {
                image.pixel(x, y).r = 1.f;
                image.pixel(x, y).g = 1.f;
                image.pixel(x, y).b = 1.f;
            }
        }
    }
}





// Fonction 13 : animation
void animation(sil::Image &image, int centre_x, int centre_y)
{
    
    for (int i = 0; i < 40; i++)
    {
        // y ne change pas 
        sil::Image new_image{image.width(), image.height()};
        int newx_postition = centre_x + i * 10;
        
        // test --> std::cout << newx_postition << std::endl;

        disque(new_image, newx_postition, centre_y);
        
        // nom du fichier
        new_image.save("output/disquegif/image_" + std::to_string(i) + ".png");
    }
    
}





// bonus
void animation_bonus(sil::Image &image, int centre_x, int centre_y)
{
    sil::Image photo{"images/dog.png"};

    for (int i = 0; i < 50; i++)
    {
        int nouveau_i = 49 - i;

        sil::Image new_image{image.width(), image.height()};

        for (int x = 0; x < photo.width(); x++)
        {
            for (int y = 0; y < photo.height(); y++)
            {
                
                int new_x = x + i * 10;
                int new_y = y;
                

                if (new_x < new_image.width())
                {
                    new_image.pixel(new_x, new_y) = photo.pixel(x, y);
                }
            }
        }
        
        new_image.save("output/animabonus/image_" + std::to_string(nouveau_i) + ".png");
    }
}





// Fonction 14 : rosace
void rosace(sil::Image &image)
{
    const double pi = 3.141592653589793;

    int centre_x = 250;
    int centre_y = 250;

    int nbcercles = 8;
    int d = 100;

    for (int i = 0; i < nbcercles; i++)
    {
        double angle = i * 2.0 * pi / nbcercles;

        int x = centre_x + d * cos(angle);
        int y = centre_y + d * sin(angle);

        cercle(image, x, y);
    }
}





// Fonction 15 : mosaique
void mosaique(sil::Image &image, std::string chemin_motif, int taille)
{
    sil::Image motif{chemin_motif};

    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            int new_x = (x * taille) % motif.width();
            int new_y = (y * taille) % motif.height();

            image.pixel(x, y) = motif.pixel(new_x, new_y);
        }
    }
}




// Fonction 16 : mosaique  miroir
void mosaique_miroir(sil::Image &image)
{
    sil::Image motif{"images/chatfusion.png"};

    int taille = 5;

    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            int new_x = (x * taille) % motif.width();
            int new_y = (y * taille) % motif.height();

            // miroir :
            if ((x * taille / motif.width()) % 2 == 1)
            {
                new_x = motif.width() - 1 - new_x;
            }

            image.pixel(x, y) = motif.pixel(new_x, new_y);
        }
    }
}




// Fonction 17 : glitch

void glitch(sil::Image &image)
{
    // pr le nb de rectangles
    for (int i = 0; i < 40; i++)
    {
        int largeur = random_int(10, 100);
        int hauteur = random_int(1, 10);

        // position des rectangles
        int x1 = random_int(0, image.width() - largeur);
        int y1 = random_int(0, image.height() - hauteur);

        int x2 = random_int(0, image.width() - largeur);
        int y2 = random_int(0, image.height() - hauteur);

        for (int x = 0; x < largeur; x++)
        {
            // bouger les pixels
            for (int y = 0; y < hauteur; y++)
            {
                glm::vec3 temp = image.pixel(x1 + x, y1 + y);

                image.pixel(x1 + x, y1 + y) = image.pixel(x2 + x, y2 + y);

                image.pixel(x2 + x, y2 + y) = temp;
            }
        }
    }
}






// Fonction 18.1 : tri de lignes
void tri_lignes(sil::Image &image)
{
    sil::Image motif{"images/logo.png"};

    // auto --> type de variable automatique
    auto &pixels = motif.pixels();

    for (int y = 0; y < motif.height(); y++)
    {
        std::sort(
            pixels.begin() + y * motif.width(),
            pixels.begin() + (y + 1) * motif.width(),

            [](glm::vec3 const &color1, glm::vec3 const &color2)
            {
                float luminosite1 = color1.r + color1.g + color1.b;
                float luminosite2 = color2.r + color2.g + color2.b;

                return luminosite1 < luminosite2;
            }
        );
    }

    image = motif;
}





// Fonction 18.2 : tri de pixels

void tri_pixels(sil::Image &image)
{
    sil::Image motif{"images/logo.png"};

    auto &pixels = motif.pixels();

    std::sort(
        pixels.begin(),
        pixels.end(),

        // ici la diff, trie direct
        [](glm::vec3 const &color1, glm::vec3 const &color2)
        {
            float luminosite1 = color1.r + color1.g + color1.b;
            float luminosite2 = color2.r + color2.g + color2.b;

            return luminosite1 < luminosite2;
        }
    );

    image = motif;
}



// Fonction 18.3 : tri pixels aléatoire
void tri_aleatoire(sil::Image &image)
{
    sil::Image motif{"images/logo.png"};

    auto &pixels = motif.pixels();

    for (int i = 0; i < 300; i++)
    {
        // ligne aleatoire
        int y = random_int(0, motif.height() - 1);

        // tri
        int debut = random_int(0, motif.width() - 1);
        int longueur = random_int(10, 100);

        int fin = std::min(debut + longueur, motif.width());

        //tri de la portion
        std::sort(
            pixels.begin() + y * motif.width() + debut,
            pixels.begin() + y * motif.width() + fin,

            [](glm::vec3 const &color1, glm::vec3 const &color2)
            {
                float luminosite1 = color1.r + color1.g + color1.b;
                float luminosite2 = color2.r + color2.g + color2.b;

                return luminosite1 < luminosite2;
            }
        );
    }

    image = motif;
}





// Fonction 19 : fractale de mandelbrot
void mandelbrot(sil::Image &image)
{
    sil::Image fractale{500, 500};

    int iterations_max = 100;

    for (int x = 0; x < fractale.width(); x++)
    {
        for (int y = 0; y < fractale.height(); y++)
        {
            // pixel en coord complexe
            float cx = (x - 250.f) / 125.f;
            float cy = (y - 250.f) / 125.f;

            // pr creer nb complexe
            std::complex<float> c{cx, cy};
            std::complex<float> z{0.f, 0.f};

            int iterations = 0;

            
            while (std::abs(z) <= 2.f && iterations < iterations_max)
            {
                z = z * z + c;
                iterations++;
            }

            float gris;
            
            if (iterations == iterations_max)
            {
                gris = 1.f;
            }
            else
            {
                gris = static_cast<float>(iterations) / iterations_max;
            }

            fractale.pixel(x, y) = glm::vec3{gris, gris, gris};
        }
    }

    image = fractale;
}








// Fonction 21 : tramage 
void tramage(sil::Image &image)
{
    // matrice de bayer
    int bayer[4][4] = {
        {0, 8, 2, 10},
        {12, 4, 14, 6},
        {3, 11, 1, 9},
        {15, 7, 13, 5}
    };

    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
        
            glm::vec3 couleur = image.pixel(x, y);

            // lminosite
            float luminosite = 0.2126f * couleur.r
                             + 0.7152f * couleur.g
                             + 0.0722f * couleur.b;

            // seul bayer
            float seuil = (bayer[y % 4][x % 4] + 0.5f) / 16.f;

            // noir ou blanc
            if (luminosite > seuil)
            {
                image.pixel(x, y) = glm::vec3(1.f, 1.f, 1.f);
            }
            else
            {
                image.pixel(x, y) = glm::vec3(0.f, 0.f, 0.f);
            }
        }
    }
}






// Fonction : kuwahara
void kuwahara(sil::Image &image, int rayon)

{
    sil::Image copie = image;

    

    for (int x = rayon; x < image.width() - rayon; x++)
    {
        for (int y = rayon; y < image.height() - rayon; y++)
        {
            glm::vec3 moyennes[4] = {
                glm::vec3(0.f),
                glm::vec3(0.f),
                glm::vec3(0.f),
                glm::vec3(0.f)
            };

            float variances[4] = {0.f, 0.f, 0.f, 0.f};

            // les 4 regions
            for (int region = 0; region < 4; region++)
            {
                int debut_x = (region == 0 || region == 2) ? -rayon : 0;
                int fin_x   = (region == 0 || region == 2) ? 0 : rayon;

                int debut_y = (region == 0 || region == 1) ? -rayon : 0;
                int fin_y   = (region == 0 || region == 1) ? 0 : rayon;

                int nombre_pixels = 0;

                // couleur moyenne
                for (int dx = debut_x; dx <= fin_x; dx++)
                {
                    for (int dy = debut_y; dy <= fin_y; dy++)
                    {
                        glm::vec3 couleur = copie.pixel(x + dx, y + dy);

                        moyennes[region] += couleur;
                        nombre_pixels++;
                    }
                }

                moyennes[region] /= float(nombre_pixels);

                // variance
                for (int dx = debut_x; dx <= fin_x; dx++)
                {
                    for (int dy = debut_y; dy <= fin_y; dy++)
                    {
                        glm::vec3 couleur = copie.pixel(x + dx, y + dy);

                        float distance = glm::distance(couleur, moyennes[region]);

                        variances[region] += distance * distance;
                    }
                }

                variances[region] /= float(nombre_pixels);
            }

            // variance + faible
            int meilleure_region = 0;

            for (int i = 1; i < 4; i++)
            {
                if (variances[i] < variances[meilleure_region])
                {
                    meilleure_region = i;
                }
            }

            // couleur moyenne de la rigion
            image.pixel(x, y) = moyennes[meilleure_region];
        }
    }
}




// Fonction : animation rosace
void animation_rosace(sil::Image &image)
{
    const double pi = 3.141592653589793;

    int centre_x = 250;
    int centre_y = 250;

    int nbcercles = 8;
    int d = 100;

    for (int i = 0; i < 40; i++)
    {
        sil::Image new_image{image.width(), image.height()};

        // on tourne la rosace
        double rotation = i * 2.0 * pi / 40;

        for (int j = 0; j < nbcercles; j++)
        {
            double angle = j * 2.0 * pi / nbcercles + rotation;

            int x = centre_x + d * cos(angle);
            int y = centre_y + d * sin(angle);

            cercle(new_image, x, y);
        }

        new_image.save("output/rosacegif/image_" + std::to_string(i) + ".png");
    }
}




int main()
{

    {
        sil::Image image{"images/logo.png"};
        keep_green_only(image);
        image.save("output/keep_green_only.png");
    }


    {
        sil::Image image{"images/logo.png"};
        channels_swap(image);
        image.save("output/channels_swap.png");
    }


    {
        sil::Image image{"images/logo.png"};
        negatif(image);
        image.save("output/negatif.png");
    }


    {
        sil::Image image{"images/logo.png"};
        noirblanc(image);
        image.save("output/noirblanc.png");
    }


    {
        sil::Image image{300, 200};
        degrade(image);
        image.save("output/degrade.png");
    }


    {
        sil::Image image{"images/logo.png"};
        miroir(image);
        image.save("output/miroir.png");
    }

    {
        sil::Image image{"images/logo.png"};
        bruitee(image);
        image.save("output/bruitee.png");
    }

    {
        sil::Image image{"images/logo.png"};
        rota90(image);
        image.save("output/rota90.png");
    }

     {
        sil::Image image{"images/logo.png"};
        rgbsplit(image);
        image.save("output/rgbsplit.png");
    }


    {
        sil::Image image{"images/photo.jpg"};
        luminosite(image);
        image.save("output/luminosite.jpg");
    }


    {
    sil::Image image{500, 500};
    disque(image, 250, 250);
    image.save("output/disque.png");
    }



    {
    sil::Image image{500, 500};
    cercle(image, 250, 250);
    image.save("output/cercle.png");
    }

    {
    sil::Image image{500, 500};
    animation(image, 100, 250);
    }



    {
    sil::Image image{500, 500};
    animation_bonus(image, 100, 250);
    }


   
    {
    sil::Image image{500, 500};
    rosace(image);
    image.save("output/rosace.png");
    }


    {
    sil::Image image{500, 500};
    mosaique(image, "images/logo.png", 2);
    image.save("output/mosaique1.png");
}


    {
    sil::Image image{500, 500};
    mosaique(image, "images/mosa.jpg", 3);
    image.save("output/mosaique1.jpg");
} 




    {
    sil::Image image{500, 500};
    mosaique_miroir(image);
    image.save("output/mosaique_miroir.png");
    }   

    


    {
    sil::Image image{"images/logo.png"};
    glitch(image);
    image.save("output/glitch.png");
    }   


    {
    sil::Image image{"images/logo.png"};
    tri_lignes(image);
    image.save("output/tri_lignes.png");
    }   


    {
    sil::Image image{"images/logo.png"};
    tri_pixels(image);
    image.save("output/tri_pixel.png");
    }   

    {
    sil::Image image{"images/logo.png"};
    tri_aleatoire(image);
    image.save("output/tri_aleatoire.png");
    }   


     {
    sil::Image image{500, 500};
    mandelbrot(image);
    image.save("output/mandelbrot.png");
    }


    {
        sil::Image image{"images/photo.jpg"};
        tramage(image);
        image.save("output/tramage.jpg");
    }

    {
        sil::Image image{"images/photo.jpg"};
        kuwahara(image, 2);
        image.save("output/kuwahara.jpg");
    }

    {
        sil::Image image{"images/chien.jpg"};
        kuwahara(image, 10);
        image.save("output/kuwahara2.jpg");
    }


    
{
    sil::Image image{500, 500};
    animation_rosace(image);

}

}