FROM nginx:1.29.1

RUN rm -rf /usr/share/nginx/html/default

COPY index.html /usr/share/nginx/html

CMD ["nginx", "-g", "daemon off;"]
