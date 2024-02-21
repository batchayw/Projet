#!/bin/sh
until nc -z -w 2 $DB_HOST 3306; do
  echo "Waiting for database..."
  sleep 2
done
echo "Database is ready."

